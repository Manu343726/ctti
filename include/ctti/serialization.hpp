#ifndef CTTI_SERIALIZATION_HPP
#define CTTI_SERIALIZATION_HPP

#include <ctti/symbol.hpp>
#include <ctti/model.hpp>
#include <vector>
#include <unordered_map>

namespace ctti
{

namespace serialization
{

template<typename Formatter, typename Output, typename T>
void serialize(Formatter formatter, Output& output, const T& value);

namespace detail
{
    template<typename T, bool IsEnum = std::is_enum<T>(), bool EmptyModel = ctti::meta::list_size<ctti::get_model<T>>() == 0>
    struct serialize
    {
        using Model = ctti::get_model<T>;

        template<typename Writer>
        struct loop_body
        {
            Writer* writer;
            const T* value;

            template<typename SymbolIdentity, typename Index>
            void operator()(SymbolIdentity, Index)
            {
                using Symbol = ctti::meta::type_t<SymbolIdentity>;
                constexpr std::size_t index = Index();

                writer->value(Symbol::symbol().str(), ctti::get_member_value<Symbol>(*value));

                if(index + 1 < ctti::meta::list_size<Model>())
                {
                    writer->value_separator();
                }
            }
        };

        template<typename Writer>
        static void apply(Writer& writer, const T& value)
        {
            loop_body<Writer> loop_body{&writer, &value};

            writer.begin_object(value);
                ctti::meta::foreach<Model>(loop_body);
            writer.end_object(value);
        }
    };

    template<typename T>
    struct serialize<T, true, false>
    {
        using Model = ctti::get_model<T>;

        template<typename Writer>
        struct loop_body
        {
            Writer* writer;
            const T* value;

            template<typename SymbolIdentity, typename Index>
            void operator()(SymbolIdentity, Index)
            {
                using Symbol = ctti::meta::type_t<SymbolIdentity>;

                if(Symbol::template get_member<T>() == *value)
                {
                    // Found the enumeration value with this value
                    writer->raw_value(Symbol::symbol().str());
                }
            }
        };

        template<typename Writer>
        static void apply(Writer& writer, const T& value)
        {
            loop_body<Writer> loop_body{&writer, &value};
            ctti::meta::foreach<Model>(loop_body);
        }
    };

    template<typename T, bool IsEnum>
    struct serialize<T, IsEnum, true>
    {
        template<typename Writer>
        static void apply(Writer& writer, const T& value)
        {
            writer.value(value);
        }
    };
}

template<typename Formatter, typename Output>
struct Writer
{
    Writer(Formatter formatter, Output& output) :
        _formatter{formatter},
        _output{&output}
    {}

    void value_separator()
    {
        _formatter.value_separator(*_output);
    }

    template<typename T>
    void raw_value(const T& value)
    {
        _formatter.raw_value(*_output, value);
    }

    template<typename T>
    void value(const T& value)
    {
        _formatter.value(*_output, value);
    }

    template<typename T>
    void value(const std::string& name, const T& value)
    {
        _formatter.value(*_output, name, value);
    }

    template<typename T>
    void begin_object(const T& object)
    {
        _formatter.begin_object(*_output, object);
    }

    template<typename T>
    void end_object(const T& object)
    {
        _formatter.end_object(*_output, object);
    }

private:
    Formatter _formatter;
    Output* _output;
};

template<typename Formatter, typename Output>
Writer<Formatter, Output> make_writer(Formatter formatter, Output& output)
{
    return {formatter, output};
}

struct ostream_otuput
{
    ostream_otuput(std::ostream& os) :
        os(&os)
    {}

    template<typename T>
    void write(const T& value)
    {
        (*os) << value;
    }

private:
    std::ostream* os;
};

struct json_formatter
{
    template<typename Output, typename T>
    void raw_value(Output& output, const T& value)
    {
        output.write(value);
    }

    template<typename Output>
    void value_separator(Output& out)
    {
        out.write(", ");
    }

    template<typename Output, typename T>
    void begin_object(Output& out, const T& object)
    {
        out.write("{");
    }

    template<typename Output, typename T>
    void end_object(Output& out, const T& object)
    {
        out.write("}");
    }

    template<typename Output, typename T>
    void value(Output& out, const std::string& name, const T& value)
    {
        out.write("\""); out.write(name); out.write("\": "); this->value(out, value);
    }

    template<typename Output, typename T>
    void value(Output& out, const T& value)
    {
        write_value(out, value, ctti::meta::bool_<ctti::meta::list_size<ctti::get_model<T>>() == 0>());
    }

    template<typename Output>
    void value(Output& out, const std::string& value)
    {
        out.write("\""); out.write(value); out.write("\"");
    }

    template<typename Output, typename T>
    void value(Output& out, const std::vector<T>& vector)
    {
        out.write("[");

        for(std::size_t i = 0; i < vector.size(); ++i)
        {
            ctti::serialization::serialize(*this, out, vector[i]);

            if(i + 1 < vector.size())
            {
                out.write(", ");
            }
        }

        out.write("]");
    }

    template<typename Output, typename Key, typename Value, typename Hash>
    void value(Output& out, const std::unordered_map<Key, Value, Hash>& map)
    {
        out.write("[");
        std::size_t i = 0;

        for(const auto& keyValue : map)
        {
            out.write("{");
            ctti::serialization::serialize(*this, out, keyValue.first);
            out.write(": ");
            ctti::serialization::serialize(*this, out, keyValue.second);
            out.write("}");

            if(i + 1 < map.size())
            {
                out.write(", ");
            }

            ++i;
        }

        out.write("]");
    }

private:
    template<typename Output, typename T>
    void write_value(Output& out, const T& value, ctti::meta::true_)
    {
        out.write(value);
    }

    template<typename Output, typename T>
    void write_value(Output& out, const T& value, ctti::meta::false_)
    {
        ctti::serialization::serialize(*this, out, value);
    }
};

template<typename Writer, typename T>
void serialize(Writer& writer, const T& value)
{
    ctti::serialization::detail::serialize<T>::apply(writer, value);
}

template<typename Formatter, typename Output, typename T>
void serialize(Formatter formatter, Output& output, const T& value)
{
    auto writer = ctti::serialization::make_writer(formatter, output);
    ctti::serialization::serialize(writer, value);
}

template<typename Formatter, typename Output, typename T>
void serialize(Formatter formatter, Output output, const T& value)
{
    auto writer = ctti::serialization::make_writer(formatter, output);
    ctti::serialization::serialize(writer, value);
}

namespace detail
{
    template<typename T, bool HasModel = ctti::meta::list_size<ctti::get_model<T>>() == 0, typename = void>
    struct is_default_ostream_serializable : public ctti::meta::false_ {};

    template<typename T>
    struct is_default_ostream_serializable<T, false, ctti::meta::void_t<decltype(T::ctti_ostream_print())>> : public ctti::meta::true_ {};

    template<typename T>
    struct is_default_ostream_serializable<T, false, ctti::meta::void_t<decltype(std::declval<T>().ctti_ostream_print())>> : public ctti::meta::true_ {};

    template<typename T>
    struct is_default_ostream_serializable<T, false, ctti::meta::void_t<decltype(ctti_ostream_print(std::declval<ctti::type_tag<T>>()))>> : public ctti::meta::true_ {};
}

}

}

template<typename T>
ctti::meta::enable_if_t<ctti::serialization::detail::is_default_ostream_serializable<T>::value, std::ostream&> operator<<(std::ostream& os, const T& value)
{
    ctti::serialization::serialize(ctti::serialization::json_formatter(), ctti::serialization::ostream_otuput(os), value);
    return os;
}

#endif // CTTI_SERIALIZATION_HPP
