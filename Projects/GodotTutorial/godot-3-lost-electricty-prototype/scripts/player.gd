extends CharacterBody2D


const SPEED = 50.0

@onready var animated_sprite: AnimatedSprite2D = $AnimatedSprite2D
@onready var tile_map: TileMap = $"../TileMap"

func get_ground() -> String:
	var tile_pos := tile_map.local_to_map(
		tile_map.to_local(global_position)
	)

	for layer in range(tile_map.get_layers_count() - 1, -1, -1):
		var tile_data := tile_map.get_cell_tile_data(layer, tile_pos)

		if tile_data:
			var type = tile_data.get_custom_data("type")
			return type

	return ""
	
func _process(delta: float) -> void:
	if get_ground() == "water":
			get_tree().reload_current_scene()

func _physics_process(delta: float) -> void:
	var directionX := Input.get_axis("ui_left", "ui_right")
	var directionY := Input.get_axis("ui_up", "ui_down")

	if directionX > 0:
		animated_sprite.flip_h = false
	elif directionX < 0:
		animated_sprite.flip_h = true
		
	if directionX != 0:
		animated_sprite.play("walkH")
	
	if directionY > 0:
		animated_sprite.play("walkDown")
	elif directionY < 0:
		animated_sprite.play("walkUp")
		
	if not directionX and not directionY:
		animated_sprite.stop()
	
	if directionX:
		velocity.x = directionX * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		
	if directionY:
		velocity.y = directionY * SPEED
	else:
		velocity.y = move_toward(velocity.y, 0, SPEED)

	move_and_slide()
