#pragma once

namespace client {
	/// <summary>
	/// Subclasses of unitRig used for rendering.
	/// </summary>
	enum class RigType {
		/// <summary>
		/// No rig, for objects that aren't rendered.
		/// </summary>
		none,
		/// <summary>
		/// Default rig for rendering a simple sprite.
		/// </summary>
		unitrig,
	};
}