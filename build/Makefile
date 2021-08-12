obj_main = main.o Render.o Matrix.o

libs_main = -lsfml-graphics -lsfml-window -lsfml-system

Render.o: ../Render.cpp
	g++ -c ../Render.cpp

Matrix.o: ../vector_lib/Matrix.cpp
	g++ -c ../vector_lib/Matrix.cpp

main.o: ../main.cpp
	g++ -c ../main.cpp

main: $(obj_main)
	g++ -o main $(obj_main) $(libs_main)

.PHONY : clean
clean:
	rm -rf *.o main