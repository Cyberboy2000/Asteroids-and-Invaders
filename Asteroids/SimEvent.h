#pragma once

/// <summary>
/// Event struct for sending data from the sim to the client.
/// </summary>
struct SimEvent {

	enum EvType {
		/// <summary>
		/// No event.
		/// </summary>
		none,
		/// <summary>
		/// Signals that a unit has been created. {unitId} is the id of the created unit. 
		/// </summary>
		unitCreated,
		/// <summary>
		/// Signals that a unit was destroyed. {unitId} is the id of the destroyed unit. 
		/// </summary>
		unitDestroyed,
	};

	/// <summary>
	/// The type of event to send. 
	/// </summary>
	EvType evType = none;
	/// <summary>
	/// The id of the primary unit subject of this event.
	/// </summary>
	int unitId = 0;
	/// <summary>
	/// The id of the second unit subject of this event.
	/// </summary>
	int targetId = 0;

	/// <summary>
	/// Construct an event with no parameters. (Currently unused)
	/// </summary>
	SimEvent(EvType evType);
	/// <summary>
	/// Construct an event with a unit parameter. (unitCreated, unitDestroyed)
	/// </summary>
	SimEvent(EvType evType, int unitId);
	/// <summary>
	/// Construct an event with a source and target unit parameters. (Currently unused)
	/// </summary>
	SimEvent(EvType evType, int unitId, int targetId);
};