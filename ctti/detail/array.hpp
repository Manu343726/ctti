#pragma once

#include <cstdint>
#include <type_traits>

namespace ctti
{
	namespace detail
	{
		template<typename T, std::size_t Size>
		struct array
		{
			template<std::size_t Begin, std::size_t End, typename T>
			static constexpr array<T, End - Begin> from_c_array(const T* arr)
			{
				return{ arr, std::make_index_sequence<End - Begin>{} };
			}

			template<typename... Elems>
			constexpr array(Elems&&... elems) :
				data_{ std::forward<Elems>(elems)... }
			{}

			constexpr const T* data() const
			{
				return &data_[0];
			}

			constexpr T operator[](std::size_t i) const
			{
				return data_[i];
			}

			constexpr std::size_t size() const
			{
				return Size;
			}

			template<std::size_t Begin, std::size_t End>
			constexpr array<T, End - Begin> subarray() const
			{
				return from_c_array<Begin, End>(data_);
			}

		private:
			const T data_[Size];

			template<std::size_t... Is>
			constexpr array(const T* arr, std::index_sequence<Is...>) :
				data_{ arr[Is]... }
			{}
		};

		template<typename T, std::size_t N>
		constexpr array<T, N> make_array(const T(&arr)[N])
		{
			return make_array<0, n>(arr);
		}

		template<typename T, std::size_t Begin, std::size_t End>
		constexpr array<T, End - Begin> make_array(const T* arr)
		{
			return array<T, End - Begin>::from_c_array<Begin, End>(arr);
		}
	}
}