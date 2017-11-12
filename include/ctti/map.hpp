#ifndef CTTI_MAP_HPP
#define CTTI_MAP_HPP

#include <ctti/symbol.hpp>

namespace ctti
{

template<typename SourceSymbol, typename SinkSymbol, typename Source, typename Sink>
constexpr void map(const Source& source, Sink& sink)
{
    ctti::get_member_value<SinkSymbol>(sink) = ctti::get_member_value<SourceSymbol>(source);
}

namespace detail
{

template<typename SourceSymbol, typename SinkSymbol>
struct symbol_map_pair
{
    constexpr symbol_map_pair() = default;
    constexpr symbol_map_pair(SourceSymbol, SinkSymbol) {}
};

}

template<typename SourceSymbol, typename SinkSymbol>
constexpr ctti::detail::symbol_map_pair<SourceSymbol, SinkSymbol> mapping()
{
    return {};
}

template<typename Source, typename Sink, typename... SourceSymbols, typename... SinkSymbols>
constexpr void map(const Source& source, Sink& sink, ctti::detail::symbol_map_pair<SourceSymbols, SinkSymbols>...)
{
    [](...){}((map<SourceSymbols, SinkSymbols>(source, sink), 0)...);
}

}

#endif // CTTI_MAP_HPP
