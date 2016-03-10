#Alfabeto
alfabeto = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
#Inicializar a variável das letras recorrentes do idioma
recorrente = ['a','e','o','s','r','d','n','i','t','m','u','l','c','v','p','g','q','b','f','h','j','x','z','k','y','w']
#Inicializar a lista em ordem alfabética das contagens
contagem = [['a', 0],['b', 0],['c', 0],['d', 0],['e', 0],['f', 0],['g', 0],['h', 0],['i', 0],['j', 0],['k', 0],['l', 0],['m', 0],['n', 0],['o', 0],['p', 0],['q', 0],['w', 0],['x', 0],['y', 0],['z', 0]]
#Entrada de texto
entrada = raw_input("Informe o texto: ")
#Tamanho da string de entrada

entrada.replace('#','')

for i in range(len(alfabeto)) :
	contagem[i][1] = entrada.count(alfabeto[i])

#Preciso colocar um for para substituir as letras em ordem de maior contagem
for i in range(len(alfabeto)) :
	


#Aqui eu coloco um for pra substituir as letras

#Aqui eu printo a mensagem decodificada
