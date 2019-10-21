#include <util/util_Misc.hpp>

namespace util
{
    ResultWith<JSON> LoadJSONFromFile(std::string path)
    {
        JSON ret = JSON::object();
        std::ifstream ifs(path);
        if(ifs.good())
        {
            ret = JSON::parse(ifs);
            return SuccessResultWith(ret);
        }
        return MakeResultWith(0xdead, ret);
    }

    std::string GetCurrentTime() // Thanks Goldleaf
    {
        time_t timet = time(NULL);
        struct tm *times = localtime((const time_t*)&timet);
        int h = times->tm_hour;
        int min = times->tm_min;
        char timestr[0x10] = {0};
        sprintf(timestr, "%02d:%02d", h, min);
        return std::string(timestr);
    }

    u32 GetBatteryLevel()
    {
        u32 perc = 0;
        psmGetBatteryChargePercentage(&perc);
        return perc;
    }

    bool IsCharging()
    {
        ChargerType ch = ChargerType_None;
        psmGetChargerType(&ch);
        return (ch > ChargerType_None);
    }
}