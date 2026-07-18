extends Node2D

@onready var timer: Timer = $Timer

var index: int = 0
var crops: Array[Node]

func _ready() -> void:
	crops = get_tree().get_nodes_in_group("crops")

func _process(delta: float) -> void:
	if not timer.is_stopped():
		return

	if crops.size() > 0:
		var crop = crops[index]
		global_position = crop.global_position
		timer.start()
		crop.harvest()

func _on_timer_timeout() -> void:
	index += 1
	if index >= crops.size():
		index = 0
