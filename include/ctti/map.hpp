#ifndef CTTI_MAP_HPP
#define CTTI_MAP_HPP

#include <ctti/symbol.hpp>

namespace ctti
{

struct default_symbol_mapping_function
{
    constexpr default_symbol_mapping_function() = default;

    template<typename Source, typename SourceSymbol, typename Sink, typename SinkSymbol>
    constexpr void operator()(const Source& source, SourceSymbol, Sink& sink, SinkSymbol) const
    {
        ctti::get_member_value<SinkSymbol>(sink) = ctti::get_member_value<SourceSymbol>(source);
    }
};

template<typename SourceSymbol, typename SinkSymbol, typename Source, typename Sink, typename Function>
constexpr void map(const Source& source, Sink& sink, const Function& function)
{
    function(source, SourceSymbol(), sink, SinkSymbol());
}

template<typename SourceSymbol, typename SinkSymbol, typename Source, typename Sink>
constexpr void map(const Source& source, Sink& sink)
{
    ctti::map<SourceSymbol, SinkSymbol>(source, sink, ctti::default_symbol_mapping_function());
}

template<typename SourceSymbol, typename SinkSymbol, typename Function = default_symbol_mapping_function>
struct symbol_mapping
{
    constexpr symbol_mapping(Function function) :
        function{function}
    {}

    Function function;
};

template<typename SourceSymbol, typename SinkSymbol, typename Function>
constexpr ctti::symbol_mapping<SourceSymbol, SinkSymbol, ctti::meta::decay_t<Function>> mapping(const Function& function)
{
    return {function};
}

template<typename SourceSymbol, typename SinkSymbol>
constexpr ctti::symbol_mapping<SourceSymbol, SinkSymbol> mapping()
{
    return {ctti::default_symbol_mapping_function()};
}

template<typename Source, typename Sink, typename... SourceSymbols, typename... SinkSymbols, typename... MappingFunctions>
constexpr void map(const Source& source, Sink& sink, const ctti::symbol_mapping<SourceSymbols, SinkSymbols, MappingFunctions>&... mapping)
{
    [](...){}((map<SourceSymbols, SinkSymbols>(source, sink, mapping.function), 0)...);
}

}

#endif // CTTI_MAP_HPP
