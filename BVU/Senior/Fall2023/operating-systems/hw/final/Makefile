test: archive runArchive unArchive runUnarchive diff

archive:
	gcc -g archive.c -o bvArchive

runArchive:
	./bvArchive sampleDir/ archive.file

unArchive:
	gcc -g unarchive.c -o bvUnarchive

runUnarchive:
	mkdir sandbox
	cd sandbox; \
	cp ../archive.file ../bvUnarchive .; \
	./bvUnarchive archive.file

diff:
	./diff.sh sampleDir/ sandbox/sampleDir/

clean:
	rm -rf sandbox bvUnarchive bvArchive archive.file

