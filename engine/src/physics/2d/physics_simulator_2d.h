#pragma once

#include "core/lumina_types.h"

#include "box2d/box2d.h"

namespace lumina
{
	class physics_simulator_2d
	{
	public:

		static constexpr const l_float32 GRAVITY = -9.8f;

		// Play's the simulation
		void play();

		// Stop's the simulation
		void pause();

		// Update's the simulation every frame
		void update(class scene* scene_ptr);

		// Wheter if the simulation is playing or not
		const bool is_playing() const { return is_playing_; }

		// Wheter if the simulation is created or not
		const bool is_created() const { return physics_world_ != nullptr; }

	private:

		// Wheter if the simulation is playing or not
		bool is_playing_ = false;

		// The physics world handler 
		b2World* physics_world_ = nullptr;

		// Create's the simulation
		void init_simulation(class scene* scene_ptr);

		// Destroy's the simulation
		void destroy_simulation();

	private:

		friend class scene;

	};
}