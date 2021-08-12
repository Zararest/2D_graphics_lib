obj_main = main.o Render.o Vector_lib.o

libs_main = -lsfml-graphics -lsfml-window -lsfml-system

Render.o: ../visual_lib/Render.cpp
	g++ -c ../visual_lib/Render.cpp

Vector_lib.o: ../vector_lib/Vector_lib.cpp
	g++ -c ../vector_lib/Vector_lib.cpp

main.o: ../main.cpp
	g++ -c ../main.cpp

main: $(obj_main)
	g++ -o main $(obj_main) $(libs_main)

.PHONY : clean
clean:
	rm -rf *.o main