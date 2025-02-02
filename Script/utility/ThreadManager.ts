namespace TwinStar.Script {

	// ------------------------------------------------

	export class ThreadManager {

		private m_pool: Array<{
			thread: Core.Miscellaneous.Thread;
			context: Core.Miscellaneous.Context;
			result: [boolean, any];
		}>;

		// ------------------------------------------------

		private make_executor(
			index: number,
			executor: () => any,
		) {
			return () => {
				let item = this.m_pool[index];
				item.context.query_byte_stream_use_big_endian().value = Core.Miscellaneous.g_context.query_byte_stream_use_big_endian().value;
				item.result = [false, undefined];
				try {
					let result = executor();
					item.result = [false, result];
				} catch (e: any) {
					item.result = [true, e];
				}
			};
		}

		// ------------------------------------------------

		constructor(
		) {
			this.m_pool = [];
		}

		// ------------------------------------------------

		idle(
			index: number
		): boolean {
			assert_test(0 <= index && index < this.m_pool.length, `invalid thread index`);
			let item = this.m_pool[index];
			return !item.context.busy().value;
		}

		execute(
			index: number,
			executor: () => any,
		): void {
			assert_test(0 <= index && index < this.m_pool.length, `invalid thread index`);
			let item = this.m_pool[index];
			assert_test(!item.context.busy().value, `context is busy`);
			item.context.execute(item.thread, this.make_executor(index, executor));
			item.thread.detach();
			return;
		}

		result(
			index: number,
		): [boolean, any] {
			assert_test(0 <= index && index < this.m_pool.length, `invalid thread index`);
			let item = this.m_pool[index];
			assert_test(!item.context.busy().value, `context is busy`);
			return item.result;
		}

		wait(
		): void {
			while (!this.m_pool.every((e, i) => (this.idle(i)))) {
				Core.Miscellaneous.Thread.yield();
			}
			return;
		}

		resize(
			size: number,
			initializer: null | (() => any) = null,
		): void {
			this.m_pool = new Array(size);
			for (let index = 0; index < size; ++index) {
				this.m_pool[index] = {
					thread: Core.Miscellaneous.Thread.default(),
					context: Core.Miscellaneous.g_context.spawn(),
					result: [false, undefined],
				};
				if (initializer !== null) {
					this.execute(index, this.make_executor(index, initializer));
				}
			}
			if (initializer !== null) {
				this.wait();
			}
			return;
		}

		push_execute(
			executor: () => any,
		): void {
			assert_test(this.m_pool.length !== 0, `thread pool is empty`);
			let index = null;
			while (index === null) {
				index = this.m_pool.findIndex((e, i) => (this.idle(i)));
				if (index === -1) {
					index = null;
					Core.Miscellaneous.Thread.yield();
				}
			}
			this.execute(index, executor);
			return;
		}

	}

	// ------------------------------------------------

	export const g_thread_manager = new ThreadManager();

	// ------------------------------------------------

}