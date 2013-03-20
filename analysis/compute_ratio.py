import subprocess

def compressed_random_size():
    p = subprocess.Popen("cat binary_output.dat | gzip | wc -c", shell=True, stdout=subprocess.PIPE)
    p.wait()
    return int(p.stdout.read().strip())

def uncompressed_random_size():
    return len(open("binary_output.dat").read())

if __name__ == "__main__":
    print "Original file size:\t", uncompressed_random_size()
    print "Compressed file size:\t", compressed_random_size()
    print "Compression ratio:\t", compressed_random_size()*1.0/uncompressed_random_size()

