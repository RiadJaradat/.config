import NN

net = NN.Network()

net.addLayer(4)
net.addLayer(3)
net.addLayer(2)

net.import_nn("./src/model.json")

while True:
    inp = input(">>> ")
    
    if inp.lower().strip() == 'quit':
        break
    
    inputVec = NN.tokenizer(inp)
    res = net.forward(inputVec)

    print("not question" if res[0] > res[1] else "question")
    
    while True:
        corr = input("is this correct? (Y/n) ")
        if corr == 'y' or corr == 'n' or corr == "":
            break
        
    if corr == 'n':
        targets = []
        if res[0] > res[1]:
            targets.append([0.00, 1.00])
        else:
            targets.append([1.00, 0.00])
        
        net.trainLoop([NN.tokenizer(inp)], targets, 200, 0.1)
        
save = input("Do you want to save the model values? (y/n) ")
while True:
    if save == 'y' or save == 'n':
        break
if save == 'y':
    net.dump_nn("./src/model.json")