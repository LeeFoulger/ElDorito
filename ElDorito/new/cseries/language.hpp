#pragma once

namespace blam
{
	enum e_language : long
	{
		_language_invalid = -1,

		_language_english,
		_language_japanese,
		_language_german,
		_language_french,
		_language_spanish,
		_language_mexican_spanish,
		_language_italian,
		_language_korean,
		_language_chinese_traditional,
		_language_chinese_simplified,
		_language_portuguese,
		_language_russian,

		k_language_count,
		k_language_default = _language_english
	};
	static_assert(sizeof(e_language) == sizeof(long));
}