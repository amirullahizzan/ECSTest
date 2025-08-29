#include <print>
#include <entt/entt.hpp>

#include "WinMain.h"
#include "../customlib/Pos.h"
#include "../customlib/DebugTools.h"
#include "../customlib/FadeBox.h"
#include "../customsrc/Scene.h"

extern Scene* currentScene_p;
extern Time gameTime;

struct Transform { float x, y; };
struct Velocity { float x, y; };
struct Color { unsigned int color; };


///SYSTEMS
void UpdateControl(entt::registry& registry)
{
	//if (GetKeyDown(KEY_INPUT_SPACE))


	if (GetKeyRepeat(KEY_INPUT_D))
	{
		auto view = registry.view<Velocity>();
		for (auto [ent, velocity] : view.each())
		{
			velocity.x += 1.0f;
		}
	}
}


unsigned int GetRandomColor()
{
	int r = std::rand() % 256; // 0-255
	int g = std::rand() % 256;
	int b = std::rand() % 256;
	return GetColor(r, g, b);
}

void GetRandomColor(entt::registry& registry)
{
	auto view = registry.view<Color>();
	for (auto [ent, color] : view.each())
	{
		color.color = GetRandomColor();
	}
}

void SpreadRandomPos(entt::registry& registry)
{
	auto view = registry.view<Transform>();
	//random spread
	for (auto [ent, transform] : view.each())
	{
		transform.x = WINDOW_W_HALF;
		transform.y = WINDOW_H_HALF;
		static constexpr int spreadRate = 10000;
		float randF = (GetRand((int)(spreadRate * 2)) - spreadRate) * 0.1f;
		transform.x += randF;
		randF = (GetRand((int)(spreadRate * 2)) - spreadRate) * 0.1f;
		transform.y += randF;
	}
}

void UpdateTransforms(entt::registry& registry)
{
	auto view = registry.view<Transform, Velocity>();

	// Lambda callback without entity
	//view.each([](auto& pos, auto& vel) { ... });

	// Lambda callback with entity
	//view.each([](auto entity, auto& pos, auto& vel) { ... });

	const float velDecay = 0.97f;
	for (auto [ent, transform, velocity] : view.each())
	{
		velocity.x *= velDecay;
		velocity.y *= velDecay;

		transform.x += velocity.x;
		transform.y += velocity.y;

	}
	auto firstEntity = *view.begin();
	auto firstViewT = view.get<Transform>(firstEntity);
	auto firstViewVel = view.get<Velocity>(firstEntity);
	//this print is not reliable because it's too heavy
	std::print("t : {}, {}", firstViewT.x, firstViewT.y);
	std::println("");
	std::print("vel : {}, {}", firstViewVel.x, firstViewVel.y);
	std::println("");
	std::print("============");
	std::println("");
}
///

void GameInit(entt::registry& registry)
{
	//currentScene_p = new MainMenuScene();
	currentScene_p = new GameScene();

	GetRandomColor();

	unsigned int defaultColor = WHITE;
	for (int i = 0u; i < 10000u; i++)
	{
		const auto entity = registry.create();

		registry.emplace<Transform>(entity, Transform{ 0.0f, 0.0f });
		registry.emplace<Velocity>(entity, Velocity{ 0.0f, 0.0f });
		registry.emplace<Color>(entity, Color{ defaultColor });
	}

	SpreadRandomPos(registry);
}

void GameUpdate(entt::registry& registry)
{
	gameTime.Update();
	currentScene_p->Update();

	//SYSTEMS
	UpdateControl(registry);
	UpdateTransforms(registry);
}

void GameDraw(entt::registry& registry)
{
	currentScene_p->Render();
	//
	FadeBox fadebox;
	fadebox.Render();
	//
	DisplayCross();

	auto view = registry.view<Transform, Color>();
	for (auto [ent, transform, color] : view.each())
	{
		DrawCircleAA(transform.x, transform.y, 20.0f, 32, color.color, 1, 1);
	}
}

void GameExit()
{
	delete currentScene_p;
}