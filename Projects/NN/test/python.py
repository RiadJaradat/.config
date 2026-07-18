import NN

net = NN.Network()

net.addLayer(4)
net.addLayer(3)
net.addLayer(2)

net.import_nn()

res = net.forward(NN.tokenizer("what are you?"))

print("not question" if res[0] > res[1] else "question")