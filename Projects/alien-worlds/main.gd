extends Node3D

@onready var env = $WorldEnvironment.environment

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


func _process(delta: float) -> void:
	var depth = max(0.0, -$Player/Head/Camera3D.global_position.y)

	if depth > 0.5:
		env.fog_enabled = true

		var t = clamp(depth / 100.0, 0.0, 1.0)

		# More fog the deeper you go
		env.fog_density = lerp(0.01, 0.12, t)

		# Darker blue
		env.fog_light_color = Color(
			0.0,
			lerp(0.40, 0.03, t),
			lerp(0.60, 0.08, t)
		)

		# Reduce ambient light
		env.ambient_light_energy = lerp(1.0, 0.15, t)

	else:
		env.fog_enabled = false
		env.ambient_light_energy = 1.0
