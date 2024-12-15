#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "SFML/Graphics.hpp"
#include "Utils.h"

using namespace sf;

TEST_CASE("Utils::LocalToGlobalPos works", "[LocalToGlobalPos]") {
	Vector2f lPos;
	Vector2f pPos;
	Vector2f gPos;

	lPos = { 0,0 }; pPos = { 0, 0 }; gPos = { 0, 0 };
	REQUIRE(Utils::LocalToGlobalPos(lPos, pPos) == gPos);

	lPos = { 10, 15 }; pPos = { 0, 0 }; gPos = { 10, 15 };
	REQUIRE(Utils::LocalToGlobalPos(lPos, pPos) == gPos);

	lPos = { 0, 0 }; pPos = { 20, 30 }; gPos = { 20, 30 };
	REQUIRE(Utils::LocalToGlobalPos(lPos, pPos) == gPos);

	lPos = { -10, -5 }; pPos = { 30, 40 }; gPos = { 20, 35 };
	REQUIRE(Utils::LocalToGlobalPos(lPos, pPos) == gPos);

	lPos = { 100, 50 }; pPos = { -50, -25 }; gPos = { 50, 25 };
	REQUIRE(Utils::LocalToGlobalPos(lPos, pPos) == gPos);

	lPos = { -100, -100 }; pPos = { 100, 100 }; gPos = { 0, 0 };
	REQUIRE(Utils::LocalToGlobalPos(lPos, pPos) == gPos);
}