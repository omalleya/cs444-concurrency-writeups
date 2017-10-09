**Enter the command below to compile both LaTeX and concurrecy:
make
    
This should compile both the LaTeX writeup and the concurrency solution. We tested many times with the default LaTeX distribution on os2.engr.oregonstate.edu. For whatever reason subfigure.sty was missing so I included the file in our tarball. Also, I needed to comment out \usepackage{pstricks, pst-node} because it was throwing an error. Please let us know if you have any troubles. We followed the intructions as best we could on the course website.

**Enter the command below to run our concurrecy program
./concurrency1
