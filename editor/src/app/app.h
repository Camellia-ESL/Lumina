#pragma once

#include "lumina.h"

namespace lumina_editor
{
	class editor_app_player : public lumina::application_player
	{
	public:

		// Called one time when app starts
		void on_init() override;

		// Called every frame before rendering
		void on_update() override;

		// Called every frame on rendering
		void on_render() override;

	private:

	};
}