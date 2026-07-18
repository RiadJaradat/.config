extends CharacterBody3D

var sensativity := 0.4

func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED

func _process(delta: float) -> void:
	if Input.is_action_just_pressed("ui_cancel"):
		Input.mouse_mode = Input.MOUSE_MODE_VISIBLE
	

func _unhandled_input(event: InputEvent) -> void:
		if event is InputEventMouseMotion:
			if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
				rotation_degrees.y -= event.relative.x * sensativity
				$Camera3D.rotation_degrees.x -= event.relative.y * sensativity
				$Camera3D.rotation_degrees.x = clamp($Camera3D.rotation_degrees.x, -30, 30)
	
