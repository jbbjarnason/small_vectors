#include <utils/meta_packed_struct.h>
#include <unit_test_core.h>

using namespace utils;
using boost::ut::operator""_test;

enum struct acs_fields 
  {
    field_1, field_2, field_3
  };

template<acs_fields tag_value>
using acs_member = member<bool,tag_value, 1>;
using metatests::constexpr_test;
using bool_bitfiled_struct = 
  meta_packed_struct<
    acs_member<acs_fields::field_1>,
    acs_member<acs_fields::field_2>,
    acs_member<acs_fields::field_3>
    >;

int main()
{
  
metatests::test_result result;
"test_bitmask"_test = [&result]
  {
  auto fn_test = []()
    {
    metatests::test_result tr;
      {
      tr |=constexpr_test(utils::bitmask_v<uint8_t,0> == 0x0u);
      tr |=constexpr_test(utils::bitmask_v<uint8_t,8> == 0xFFu);
      tr |=constexpr_test(utils::bitmask_v<uint8_t,7> == 0x7Fu);
      tr |=constexpr_test(utils::bitmask_v<uint8_t,1> == 0x1u);
      
      tr |=constexpr_test(utils::bitmask_v<uint16_t,7> == 0x7Fu);
      tr |=constexpr_test(utils::bitmask_v<uint16_t,1> == 0x1u);
      tr |=constexpr_test(utils::bitmask_v<uint16_t,8> == 0xFFu);
      tr |=constexpr_test(utils::bitmask_v<uint16_t,13> == (1u<<13)-1);
      tr |=constexpr_test(utils::bitmask_v<uint16_t,9> == (1u<<9)-1);
      tr |=constexpr_test(utils::bitmask_v<uint16_t,16> == 0xFFFFu);
      
      tr |=constexpr_test(utils::bitmask_v<uint32_t,8> == 0xFFu);
      tr |=constexpr_test(utils::bitmask_v<uint32_t,7> == 0x7Fu);
      tr |=constexpr_test(utils::bitmask_v<uint32_t,1> == 0x1u);
      tr |=constexpr_test(utils::bitmask_v<uint32_t,28> == (1u<<28)-1);
      tr |=constexpr_test(utils::bitmask_v<uint32_t,23> == (1u<<23)-1);
      tr |=constexpr_test(utils::bitmask_v<uint32_t,29> == (1u<<29)-1);
      tr |=constexpr_test(utils::bitmask_v<uint32_t,32> == 0xFFFFFFFFu);
      
      tr |=constexpr_test(utils::bitmask_v<uint64_t,0> == 0x0u);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,8> == 0xFFu);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,7> == 0x7Fu);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,1> == 0x1u);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,28> == (1u<<28)-1);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,23> == (1u<<23)-1);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,29> == (1u<<29)-1);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,32> == 0xFFFFFFFFu);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,58> == (1LLu<<58)-1);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,53> == (1LLu<<53)-1);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,59> == (1LLu<<59)-1);
      tr |=constexpr_test(utils::bitmask_v<uint64_t,64> == 0xFFFFFFFFFFFFFFFFLLu);
      }
      
    return tr;
    };
  result |= metatests::run_constexpr_test(fn_test);
  result |= metatests::run_consteval_test(fn_test);
  };
  
"test_metabitstruct_bool"_test = [&result]
  {
  auto fn_test = []()
    {
    metatests::test_result tr;
    using enum acs_fields;
    constexpr auto fcount = filed_count<bool_bitfiled_struct>();
    tr |= constexpr_test(fcount == 3);
    constexpr auto s_bit_width = bit_width<bool_bitfiled_struct>();
    tr |= constexpr_test(s_bit_width == 3);
      {
      bool_bitfiled_struct acr;
      decltype(auto) cacr{ const_cast<bool_bitfiled_struct const &>(acr) };

      get<field_1>(acr) = true;
      get<field_3>(acr) = true;

      auto res = get<field_1>(cacr);
      tr |=constexpr_test(res == true );
      res = get<field_2>(acr);
      tr |=constexpr_test(res == false );

      auto packed_value = pack_value<uint8_t>(acr);
      tr |=constexpr_test(packed_value == 0b101 );
      }

      {
      bool_bitfiled_struct acr;
      decltype(auto) cacr{ const_cast<bool_bitfiled_struct const &>(acr) };

      get<field_1>(acr) = true;

      auto res = get<field_1>(cacr);
      tr |=constexpr_test(res == true );
      res = get<field_2>(acr);
      tr |=constexpr_test(res == false );
      res = get<field_3>(acr);
      tr |=constexpr_test(res == false );

      auto packed_value = pack_value<uint8_t>(acr);
      tr |=constexpr_test(packed_value == 0b001 );
      }
      {
      bool_bitfiled_struct acr;
      decltype(auto) cacr{ const_cast<bool_bitfiled_struct const &>(acr) };
      auto res = get<field_1>(cacr);
      tr |=constexpr_test(res == false );

      get<field_2>(acr) = true;

      tr |=constexpr_test(get<field_1>(acr) == false );
      tr |=constexpr_test(get<field_2>(acr) == true );
      tr |=constexpr_test(get<field_3>(acr) == false );

      auto packed_value = pack_value<uint8_t>(acr);
      tr |=constexpr_test(packed_value == 0b010 );
      }
    return tr;
    };
  result |= metatests::run_constexpr_test(fn_test);
  result |= metatests::run_consteval_test(fn_test);
  };

  
enum struct mbs_fields 
  {
    field_1, field_2, field_3, field_4
  };
enum struct example_enum_value : uint8_t
  { value0 = 0, value1, value2, value3 };
  
using mixed_bitfiled_struct = 
  meta_packed_struct<
    member<uint8_t,mbs_fields::field_1,4>,
    member<bool,mbs_fields::field_2,1>,
    member<uint32_t ,mbs_fields::field_3,32>,
    member<example_enum_value, mbs_fields::field_4,3>
    >;
    
"test_metabitstruct_mixed"_test = [&result]
  {
  auto fn_test = []()
    {
    metatests::test_result tr;
    using enum mbs_fields;
    constexpr auto fcount = filed_count<mixed_bitfiled_struct>();
    tr |= constexpr_test(fcount == 4);
    constexpr auto s_bit_width = bit_width<mixed_bitfiled_struct>();
    tr |= constexpr_test(s_bit_width == 40);
      {
      mixed_bitfiled_struct mbs;
      get<field_1>(mbs) = 0b1111;
      tr |= constexpr_test(get<field_1>(mbs) == 0b1111 );
      tr |= constexpr_test(get<field_2>(mbs) == false );
      tr |= constexpr_test(get<field_3>(mbs) == 0 );
      tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

      auto packed_value = pack_value<uint64_t>(mbs);
      tr |= constexpr_test(packed_value == 0b1111 );
      }
      {
      mixed_bitfiled_struct mbs;
      get<field_2>(mbs) = true;
      tr |= constexpr_test(get<field_1>(mbs) == 0 );
      tr |= constexpr_test(get<field_2>(mbs) == true );
      tr |= constexpr_test(get<field_3>(mbs) == 0 );
      tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

      auto packed_value = pack_value<uint64_t>(mbs);
      tr |= constexpr_test(packed_value == 0b10000 );
      }
      {
      mixed_bitfiled_struct mbs;
      get<field_3>(mbs) = 0xffff;
      tr |= constexpr_test(get<field_1>(mbs) == 0 );
      tr |= constexpr_test(get<field_2>(mbs) == false );
      tr |= constexpr_test(get<field_3>(mbs) == 0xffff );
      tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

      auto packed_value = pack_value<uint64_t>(mbs);
      tr |= constexpr_test(packed_value == 0b00'1111111111111111'0'0000 );
      }
      {
      using enum example_enum_value;
      mixed_bitfiled_struct mbs;
      get<field_2>(mbs) = true;
      get<field_3>(mbs) = 0x0ff0;
      get<field_4>(mbs) = value2;
      tr |= constexpr_test(get<field_1>(mbs) == 0 );
      tr |= constexpr_test(get<field_2>(mbs) == true );
      tr |= constexpr_test(get<field_3>(mbs) == 0x0ff0 );
      tr |= constexpr_test(get<field_4>(mbs) == value2 );

      auto packed_value = pack_value<uint64_t>(mbs);
      tr |= constexpr_test(packed_value == 0b10'00000000000000000000111111110000'1'0000 );
      }
    return tr;
    };
  result |= metatests::run_constexpr_test(fn_test);
  result |= metatests::run_consteval_test(fn_test);
  };
  
  using mixed_bitfiled_struct2 = 
    meta_packed_struct<
      member<uint8_t,mbs_fields::field_1,4>,
      member<bool,mbs_fields::field_2,1>,
      member<uint16_t ,mbs_fields::field_3,16>,
      member<example_enum_value, mbs_fields::field_4,3>
      >;
  "test_metabitstruct_mixed2"_test = [&result]
    {
    auto fn_test = []()
      {
      metatests::test_result tr;
      using enum mbs_fields;
      constexpr auto fcount = filed_count<mixed_bitfiled_struct2>();
      tr |= constexpr_test(fcount == 4);
      constexpr auto s_bit_width = bit_width<mixed_bitfiled_struct2>();
      tr |= constexpr_test(s_bit_width == 24);
        {
        mixed_bitfiled_struct2 mbs;
        get<field_1>(mbs) = 0b1111;
        tr |= constexpr_test(get<field_1>(mbs) == 0b1111 );
        tr |= constexpr_test(get<field_2>(mbs) == false );
        tr |= constexpr_test(get<field_3>(mbs) == 0 );
        tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

        auto packed_value = pack_value<uint32_t>(mbs);
        tr |= constexpr_test(packed_value == 0b1111 );
        }
        {
        mixed_bitfiled_struct2 mbs;
        get<field_2>(mbs) = true;
        tr |= constexpr_test(get<field_1>(mbs) == 0 );
        tr |= constexpr_test(get<field_2>(mbs) == true );
        tr |= constexpr_test(get<field_3>(mbs) == 0 );
        tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

        auto packed_value = pack_value<uint32_t>(mbs);
        tr |= constexpr_test(packed_value == 0b10000 );
        }
        {
        mixed_bitfiled_struct2 mbs;
        get<field_3>(mbs) = 0xffff;
        tr |= constexpr_test(get<field_1>(mbs) == 0 );
        tr |= constexpr_test(get<field_2>(mbs) == false );
        tr |= constexpr_test(get<field_3>(mbs) == 0xffff );
        tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

        auto packed_value = pack_value<uint32_t>(mbs);
        tr |= constexpr_test(packed_value == 0b00'1111111111111111'0'0000 );
        }
        {
        using enum example_enum_value;
        mixed_bitfiled_struct2 mbs;
        get<field_2>(mbs) = true;
        get<field_3>(mbs) = 0x0ff0;
        get<field_4>(mbs) = value2;
        tr |= constexpr_test(get<field_1>(mbs) == 0 );
        tr |= constexpr_test(get<field_2>(mbs) == true );
        tr |= constexpr_test(get<field_3>(mbs) == 0x0ff0 );
        tr |= constexpr_test(get<field_4>(mbs) == value2 );

        auto packed_value = pack_value<uint32_t>(mbs);
        tr |= constexpr_test(packed_value == 0b10'0000111111110000'1'0000 );
        }
      return tr;
      };
    result |= metatests::run_constexpr_test(fn_test);
    result |= metatests::run_consteval_test(fn_test);
    };
    
  using mixed_bitfiled_struct3 = 
    meta_packed_struct<
      member<uint8_t,mbs_fields::field_1,4>,
      member<bool,mbs_fields::field_2,1>,
      member<uint64_t ,mbs_fields::field_3,56>,
      member<example_enum_value, mbs_fields::field_4,3>
      >;
  "test_metabitstruct_mixed3"_test = [&result]
    {
    auto fn_test = []()
      {
      metatests::test_result tr;
      using enum mbs_fields;
      constexpr auto fcount = filed_count<mixed_bitfiled_struct3>();
      tr |= constexpr_test(fcount == 4);
      constexpr auto s_bit_width = bit_width<mixed_bitfiled_struct3>();
      tr |= constexpr_test(s_bit_width == 64);
        {
        mixed_bitfiled_struct3 mbs;
        get<field_1>(mbs) = 0b1111;
        tr |= constexpr_test(get<field_1>(mbs) == 0b1111 );
        tr |= constexpr_test(get<field_2>(mbs) == false );
        tr |= constexpr_test(get<field_3>(mbs) == 0 );
        tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

        auto packed_value = pack_value<uint64_t>(mbs);
        tr |= constexpr_test(packed_value == 0b1111 );
        }
        {
        mixed_bitfiled_struct3 mbs;
        get<field_2>(mbs) = true;
        tr |= constexpr_test(get<field_1>(mbs) == 0 );
        tr |= constexpr_test(get<field_2>(mbs) == true );
        tr |= constexpr_test(get<field_3>(mbs) == 0 );
        tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

        auto packed_value = pack_value<uint64_t>(mbs);
        tr |= constexpr_test(packed_value == 0b10000 );
        }
        {
        mixed_bitfiled_struct3 mbs;
        get<field_3>(mbs) = (0x1llu<<56)-1;
        tr |= constexpr_test(get<field_1>(mbs) == 0 );
        tr |= constexpr_test(get<field_2>(mbs) == false );
        tr |= constexpr_test(get<field_3>(mbs) == (0x1llu<<56)-1 );
        tr |= constexpr_test(get<field_4>(mbs) == example_enum_value{} );

        auto packed_value = pack_value<uint64_t>(mbs);
        tr |= constexpr_test(packed_value == 0b00'11111111111111111111111111111111111111111111111111111111'0'0000 );
        }
        {
        using enum example_enum_value;
        mixed_bitfiled_struct3 mbs;
        get<field_2>(mbs) = true;
        get<field_3>(mbs) = 0b01111111111111111111111111111111111111111111111111111110;
        get<field_4>(mbs) = value2;
        tr |= constexpr_test(get<field_1>(mbs) == 0 );
        tr |= constexpr_test(get<field_2>(mbs) == true );
        tr |= constexpr_test(get<field_3>(mbs) == 0b01111111111111111111111111111111111111111111111111111110 );
        tr |= constexpr_test(get<field_4>(mbs) == value2 );

        auto packed_value = pack_value<uint64_t>(mbs);
        tr |= constexpr_test(packed_value == 0b10'01111111111111111111111111111111111111111111111111111110'1'0000 );
        
        }
      return tr;
      };
    result |= metatests::run_constexpr_test(fn_test);
    result |= metatests::run_consteval_test(fn_test);
    };
    
"test_metabitstruct_mixed_constrcution"_test = [&result]
  {
  auto fn_test = []()
    {
    metatests::test_result tr;
    using enum mbs_fields;
    using enum example_enum_value;

    mixed_bitfiled_struct mbs
      {
      arg<field_1> = uint8_t{1u},
      arg<field_2> = true,
      arg<field_3> = uint16_t{0x0ff0u},
      arg<field_4> = value1
      };
    tr |= constexpr_test(get<field_1>(mbs) == 1 );
    tr |= constexpr_test(get<field_2>(mbs) == true );
    tr |= constexpr_test(get<field_3>(mbs) == 0x0ff0 );
    tr |= constexpr_test(get<field_4>(mbs) == value1 );
    return tr;
    };
  result |= metatests::run_constexpr_test(fn_test);
  result |= metatests::run_consteval_test(fn_test);
  };

"test_metabitstruct2_mixed_unpack"_test = [&result]
  {
  auto fn_test = []()
    {
    metatests::test_result tr;
    using enum mbs_fields;
    using enum example_enum_value;

    uint32_t packed_value{ 0b011000011111111000010010 };
    auto mbs{ unpack_value<mixed_bitfiled_struct2>(packed_value) };

    tr |= constexpr_test(get<field_1>(mbs) == 0x02 );
    tr |= constexpr_test(get<field_2>(mbs) == true );
    tr |= constexpr_test(get<field_3>(mbs) == 0x0ff0 );
    tr |= constexpr_test(get<field_4>(mbs) == value3 );

    return true;
    };
  result |= metatests::run_constexpr_test(fn_test);
  result |= metatests::run_constexpr_test(fn_test);
  };

"test_metabitstruct_mixed_unpack"_test = [&result]
  {
  auto fn_test = []()
    {
    metatests::test_result tr;
    using enum mbs_fields;
    using enum example_enum_value;

    mixed_bitfiled_struct mbs;
    get<field_1>(mbs) = 0b1011;
    get<field_2>(mbs) = false;
    get<field_3>(mbs) = 0b10101010101010101010101010101010;
    get<field_4>(mbs) = value1;

    auto packed_value{ pack_value<uint64_t>(mbs) };

    auto mbs_unpacked{ unpack_value<decltype(mbs)>(packed_value) };
    tr |= constexpr_test(get<field_1>(mbs) == get<field_1>(mbs_unpacked));
    tr |= constexpr_test(get<field_2>(mbs) == get<field_2>(mbs_unpacked));
    tr |= constexpr_test(get<field_3>(mbs) == get<field_3>(mbs_unpacked));
    tr |= constexpr_test(get<field_4>(mbs) == get<field_4>(mbs_unpacked));

    return true;
    };
  result |= metatests::run_constexpr_test(fn_test);
  result |= metatests::run_constexpr_test(fn_test);
  };
return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
