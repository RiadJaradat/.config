extends CharacterBody3D

@export var sensitivity := 0.005
@export var speed := 4.0
@export var gravity := 9.8
@export var water_drag := 3.0
@export var swim_force := 15.0

var swim_input := 0.0

func _ready() -> void:
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	
func _unhandled_input(event: InputEvent) -> void:
	if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		if event is InputEventMouseMotion:
			rotate_y(-event.relative.x * sensitivity)
			$Head.rotate_x(-event.relative.y * sensitivity) 
			$Head.rotation.x = clamp($Head.rotation.x, deg_to_rad(-55), deg_to_rad(60))
	
func _process(delta: float) -> void:
	if Input.is_action_just_pressed("ui_cancel"):
		if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
			Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
		else:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
		
	
func _physics_process(delta: float) -> void:
	
	swim_input = 0.0
	
	if Input.is_action_pressed("swim_up"):
		swim_input += 1

	if Input.is_action_pressed("swim_down"):
		swim_input -= 1
	
	var input := Input.get_vector(
		"move_left",
		"move_right",
		"move_backward",
		"move_forward"
	)
	
	var direction := (
		transform.basis.x * input.x +
		-transform.basis.z * input.y
	).normalized()
	
	var target_velocity := direction * speed
	
	if global_position.y > 0.1: # above water
		velocity.x = target_velocity.x
		velocity.z = target_velocity.z
		velocity.y -= gravity * delta

	else:
		velocity.x = lerp(velocity.x, target_velocity.x, water_drag * delta)
		velocity.z = lerp(velocity.z, target_velocity.z, water_drag * delta)
		
		velocity.y += swim_input * swim_force * delta
		
		velocity.y = lerp(
			velocity.y,
			0.0,
			water_drag * delta
		)
		
	move_and_slide()
	
	
