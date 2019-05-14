#ifndef CANTYPES_HPP_ML9DFK7A
#define CANTYPES_HPP_ML9DFK7A

#include <cstdint>
#include <map>
#include <string>
#include <vector>

enum class CANsignalType { Int, Float, String };
enum class CANsignalMuxType { NotMuxed = 0, Muxer, Muxed };
enum class CANsignalEndianness { BigEndianMotorola = 0, LittleEndianIntel = 1 };

struct CANsignal {
    std::string signal_name;
    std::uint8_t startBit;
    std::uint8_t signalSize;
    CANsignalEndianness endianness;
    bool valueSigned;
    float factor;
    float offset;
    float min;
    float max;
    std::string unit;
    std::vector<std::string> receivers;
    CANsignalMuxType muxType{ CANsignalMuxType::NotMuxed };
    std::uint8_t muxNdx{ 0 };

    bool operator==(const CANsignal& rhs) const
    {
        return signal_name == rhs.signal_name;
    }
};

struct CANmessage {
    // Constructor required for vs2015 to be able to use initializer_list
    CANmessage(std::uint32_t _id, const std::string& _name = "",
        std::uint32_t _dlc = 0, const std::string& _ecu = "")
        : id(_id)
        , name(_name)
        , dlc(_dlc)
        , ecu(_ecu)
    {
    }

    std::uint32_t id;
    std::string name;
    std::uint32_t dlc;
    std::string ecu;
    std::uint32_t updateCycle{ 0 };
    std::string initValue{ "" };
};

namespace std {
template <> struct less<CANmessage> {
    bool operator()(const CANmessage& lhs, const CANmessage& rhs) const
    {
        return lhs.id < rhs.id;
    }
};
} // namespace std

using CANmessages_t = std::map<CANmessage, std::vector<CANsignal>>;

struct CANdb_t {
    struct ValTable {
        std::string identifier;

        struct ValTableEntry {
            std::uint32_t id;
            std::string ident;
        };
        std::vector<ValTableEntry> entries;
    };

    std::map<CANmessage, std::vector<CANsignal>> messages;
    std::string version;
    std::vector<std::string> nodes;
    std::vector<std::string> symbols;
    std::vector<std::string> ecus;
    std::vector<ValTable> val_tables;
};

#endif /* end of include guard: CANTYPES_HPP_ML9DFK7A */
