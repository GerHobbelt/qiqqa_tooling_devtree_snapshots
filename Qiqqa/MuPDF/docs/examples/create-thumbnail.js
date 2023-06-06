// Create a PDF containing thumbnails of pages rendered from another PDF.

if (scriptArgs.length < 2) {
	print("usage: mutool run create-thumbnail.js input.pdf output.pdf");
	quit();
}

var pdf = new PDFDocument()

var subdoc = Document.openDocument(scriptArgs[0]) // "pdfref17.pdf"

var resources = { XObject: {} }

var contents = new Buffer()
for (var i=0; i < 5; ++i) {
	var pixmap = subdoc.loadPage(1140+i).toPixmap([0.2,0,0,0.2,0,0], ColorSpace.DeviceRGB, true)
	resources.XObject["Im" + i] = pdf.addImage(new Image(pixmap))
	contents.writeLine("q 100 0 0 150 " + (50+100*i) + " 50 cm /Im" + i + " Do Q")
}

var page = pdf.addPage([0,0,100+i*100,250], 0, resources, contents)
pdf.insertPage(-1, page)

pdf.save(scriptArgs[1]) // "out.pdf"
