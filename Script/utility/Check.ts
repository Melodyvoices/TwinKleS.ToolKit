namespace TwinStar.Check {

	// ------------------------------------------------

	export type Checker<T> = (value: T) => boolean;

	export type CheckerX<T> = (value: T) => null | string;

	// ------------------------------------------------

	export function enumeration_checker_x<T>(
		rule: Array<T>,
	): CheckerX<T> {
		return (value) => (rule.includes(value) ? null : los('须为其中之一：{}', `[ ${rule.join(' , ')} ]`));
	}

	export function regexp_checker_x(
		rule: RegExp,
	): CheckerX<string> {
		return (value) => (rule.test(value) ? null : los('须匹配正则式：{}', `${rule.source}`));
	}

	// ------------------------------------------------

}