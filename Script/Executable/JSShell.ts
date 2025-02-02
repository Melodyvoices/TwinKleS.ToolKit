/** 提供JS交互模式命令行 */
namespace TwinStar.Script.Executable.JSShell {

	export function execute(
	): void {
		Console.information(los('executable.js_shell:input_start'), [
			los('executable.js_shell:input_description'),
		]);
		while (true) {
			let script = '';
			while (true) {
				let sub_script = Console.string(true, null);
				if (sub_script === null) {
					break;
				}
				script += sub_script + '\n';
			}
			if (script === '') {
				break;
			}
			try {
				let result = CoreX.Miscellaneous.evaluate(script, '<unnamed>', false);
				Console.success(`> ${result}`, []);
			} catch (e: any) {
				Console.error_of(e);
			}
		}
		return;
	}

}

TwinStar.Script.Executable.JSShell.execute();