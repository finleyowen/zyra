# move into the program directory to build it
cd ../..

# build the compiler
make -B

# create the output file
echo "#include <memory>
class MyClass;" > ./demos/v0.0.1/sample.out.cpp

# run the Zyra compiler
./zc < ./demos/v0.0.1/sample.in.z > ./demos/v0.0.1/sample.out.cpp

# generate the side-by-side comparison
> ./demos/v0.0.1/diff.txt
diff -y -w --width=160 ./demos/v0.0.1/sample.in.z ./demos/v0.0.1/sample.out.cpp\
	> ./demos/v0.0.1/diff.txt