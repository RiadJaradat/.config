extends Node2D

@export var isAppleType: bool = false
@export var growth: int = 1
@export var harvestable: bool = false

@onready var sprite: Sprite2D = $Sprite2D
@onready var timer: Timer = $Timer

var growTime: float = randf_range(1.5, 5)

var growLimit: int = 4

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	timer.wait_time = growTime
	timer.start()
	add_to_group("crops")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	sprite.region_rect.position.x = 16 * growth
	sprite.region_rect.position.y = int(isAppleType)

func _on_timer_timeout() -> void:
	if growth < growLimit:
		growth += 1

		timer.stop()
		timer.wait_time = randf_range(1.5, 5.0)
		timer.start()
	else:
		timer.stop()
		harvestable = true
		
func harvest():
	if growth >= growLimit and harvestable:
		growth = 1
		harvestable = false
		
		timer.wait_time = randf_range(1.5, 5.0)
		timer.start()
	
