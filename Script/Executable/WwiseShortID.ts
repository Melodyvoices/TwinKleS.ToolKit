/** 计算 Wwise Short ID */
namespace TwinStar.Executable.WwiseShortID {

	export function execute(
	): void {
		Console.notify('i', los(`请输入 Wwise ID 字符串`), []);
		while (true) {
			let name = Console.string(null).toLowerCase();
			let value = CoreX.Tool.Data.Hash.FNV.hash_s(name, 'm_1', 'b_32');
			Console.notify('s', `${value}`, []);
		}
		return;
	}

}

TwinStar.Executable.WwiseShortID.execute();