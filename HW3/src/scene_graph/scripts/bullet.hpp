#pragma once

#include "scene_graph/script.hpp"
namespace W3D::sg
{
class Bullet : public NodeScript
{
  private:
	float                             speed_multiplier_ = 2.0f;
	std::unordered_map<KeyCode, bool> key_pressed_;
	bool                              selected = false;

  public:
	static const float TRANSLATION_MOVE_STEP;

	/*
	 * Constructor simply sends the node argument to its parent constructor.
	 */
	Bullet(Node &node);

	/*
	 * Called each frame, this function updates the player's state. Note, if a key
	 * for controlling the player is pressed it will respond here for movement.
	 */
	void update(float delta_time) override;

	void pryamid_rotate(float delta_time);

	/*
	 * When the player is the active object that can be moved it will be asked to
	 * respond to events like key presses.
	 */
	//void process_event(const Event &event) override;
	void toggle_select_on();
	void toggle_select_off();
};
}        // namespace W3D::sg