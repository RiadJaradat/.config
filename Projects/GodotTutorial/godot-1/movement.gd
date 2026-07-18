extends CharacterBody3D

@export var speed := 5.0
@export var gravity := 9.8

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	print("running")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	var input = Input.get_vector(
		"move_left",
		"move_right",
		"move_backward",
		"move_forward"
	)
	
	var direction = (
		transform.basis.x * input.x +
		-transform.basis.z * input.y
	).normalized()
	
	velocity.x = direction.x * speed;
	velocity.z = direction.z * speed;
	velocity.y += gravity * delta
	
	move_and_slide();
