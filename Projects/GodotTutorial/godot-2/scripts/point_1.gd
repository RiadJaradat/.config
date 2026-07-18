extends Area2D

@onready var camera: Camera2D = $"../Player/Camera2D"
@export var smothingOut: float = 0.8
@export var smothingIn: float = 3.5

var isEntered: bool = false

var min: int = 1
var max: int = 4

func _on_body_exited(body: Node2D) -> void:
	isEntered = false


func _on_body_entered(body: Node2D) -> void:
	isEntered = true

func _process(delta: float) -> void:
	if isEntered:
		if camera.zoom.x > min:
			camera.zoom.x -= smothingOut * delta
		else:
			camera.zoom.x = min
			
		if camera.zoom.y > min:
			camera.zoom.y -= smothingOut * delta
		else:
			camera.zoom.y = min
	else:
		#camera.zoom.x = 4
		#camera.zoom.y = 4
		
		if camera.zoom.x < max:
			camera.zoom.x += smothingIn * delta
		else:
			camera.zoom.x = max
			
		if camera.zoom.y < max:
			camera.zoom.y += smothingIn * delta
		else:
			camera.zoom.y = max
