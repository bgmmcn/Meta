/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITYCORE_INSPECT_PACKETS_H
#define TRINITYCORE_INSPECT_PACKETS_H

#include "Packet.h"
#include "CharacterPackets.h"
#include "DBCEnums.h"
#include "ItemPacketsCommon.h"
#include "ObjectGuid.h"
#include "RaceMask.h"
#include "SharedDefines.h"
#include "TraitPacketsCommon.h"

class Item;
class Player;

namespace WorldPackets
{
    namespace Inspect
    {
        class Inspect final : public ClientPacket
        {
        public:
            explicit Inspect(WorldPacket&& packet) : ClientPacket(CMSG_INSPECT, std::move(packet)) { }

            void Read() override;

            ObjectGuid Target;
        };

        struct InspectEnchantData
        {
            InspectEnchantData(uint32 id, uint8 index) : Id(id), Index(index) { }

            uint32 Id = 0;
            uint8 Index = 0;
        };

        struct AzeriteEssenceData
        {
            uint32 Index = 0;
            uint32 AzeriteEssenceID = 0;
            uint32 Rank = 0;
            bool SlotUnlocked = false;
        };

        struct InspectItemData
        {
            InspectItemData(::Item const* item, uint8 index);

            ObjectGuid CreatorGUID;
            Item::ItemInstance Item;
            uint8 Index = 0;
            bool Usable = false;
            std::vector<InspectEnchantData> Enchants;
            std::vector<Item::ItemGemData> Gems;
            std::vector<int32> AzeritePowers;
            std::vector<AzeriteEssenceData> AzeriteEssences;
        };

        struct PlayerModelDisplayInfo
        {
            ObjectGuid GUID;
            std::vector<InspectItemData> Items;
            std::string Name;
            int32 SpecializationID = 0;
            uint8 GenderID = GENDER_NONE;
            uint8 Race = RACE_NONE;
            uint8 ClassID = CLASS_NONE;
            std::vector<Character::ChrCustomizationChoice> Customizations;

            void Initialize(Player const* player);
        };

        struct InspectGuildData
        {
            ObjectGuid GuildGUID;
            int32 NumGuildMembers = 0;
            int32 AchievementPoints = 0;
        };

        struct PVPBracketData
        {
            int32 Rating = 0;
            int32 RatingID = 0;
            int32 Rank = 0;
            int32 WeeklyPlayed = 0;
            int32 WeeklyWon = 0;
            int32 SeasonPlayed = 0;
            int32 SeasonWon = 0;
            int32 WeeklyBestRating = 0;
            int32 LastWeeksBestRating = 0;
            int32 Tier = 0;
            int32 WeeklyBestTier = 0;
            int32 SeasonBestRating = 0;
            uint8 SeasonBestTierEnum = 0;
            int32 RoundsSeasonPlayed = 0;
            int32 RoundsSeasonWon = 0;
            int32 RoundsWeeklyPlayed = 0;
            int32 RoundsWeeklyWon = 0;
            uint8 Bracket = 0;
            bool Disqualified = false;
        };

        struct TraitInspectInfo
        {
            int32 Level = 0;
            int32 ChrSpecializationID = 0;
            Traits::TraitConfig Config;
        };

        class InspectResult final : public ServerPacket
        {
        public:
            explicit InspectResult() : ServerPacket(SMSG_INSPECT_RESULT, 4096) { }

            WorldPacket const* Write() override;

            PlayerModelDisplayInfo DisplayInfo;
            std::vector<uint16> Glyphs;
            std::vector<uint16> Talents;
            std::array<uint16, MAX_PVP_TALENT_SLOTS> PvpTalents = { };
            Optional<InspectGuildData> GuildData;
            std::array<PVPBracketData, 9> Bracket;
            Optional<int32> AzeriteLevel;
            int32 ItemLevel = 0;
            uint32 LifetimeHK = 0;
            uint32 HonorLevel = 0;
            uint16 TodayHK = 0;
            uint16 YesterdayHK = 0;
            uint8 LifetimeMaxRank = 0;
            TraitInspectInfo TalentTraits;
        };

        class QueryInspectAchievements final : public ClientPacket
        {
        public:
            explicit QueryInspectAchievements(WorldPacket&& packet) : ClientPacket(CMSG_QUERY_INSPECT_ACHIEVEMENTS, std::move(packet)) { }

            void Read() override;

            ObjectGuid Guid;
        };

        /// RespondInspectAchievements in AchievementPackets
    }
}

#endif // TRINITYCORE_INSPECT_PACKETS_H
