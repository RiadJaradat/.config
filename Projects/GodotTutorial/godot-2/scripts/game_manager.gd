extends Node

var score: int = 0

@onready var score_label: Label = $ScoreLabel

func _ready() -> void:
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func add_point():
	score += 1
	score_label.text = "Total coins collected: " + str(score) + "/10"
