#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <leptonica/pix_internal.h>
#include <string>
#include <fstream>
//#include <libgen.h>

#include "monolithic_examples.h"


static const char *basename(const char *p)
{
	const char *f = strrchr(p, '/');
	if (f)
		f++;
	else
		f = p;
	p = f;
	f = strrchr(p, '\\');
	if (f)
		f++;
	else
		f = p;
	return f;
}


#if defined(BUILD_MONOLITHIC)
#define main tesslinesplit_kraken_main
#endif

int main(int argc, const char **argv) {
  if((argc != 3) && (argc != 4)) { printf("USAGE: %s imagefile outputjson [lang]\n", argv[0]); return 1; }

  std::string input_filename = std::string(argv[1]);
  std::string input_basename = std::string(basename(argv[1]));

  std::string output_json_filename = std::string(argv[2]);
  std::ofstream output_json;

  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (argc == 4) {
    api->InitSimple(nullptr, argv[3]);
  }
  else {
    api->InitSimple(nullptr, "eng");
  }
  Pix *image0 = pixRead(input_filename.c_str());
  api->SetImage(image0);
  Pix* image = api->GetThresholdedImage();
  api->SetImage(image);
  Boxa* boxes = api->GetComponentImages(tesseract::RIL_TEXTLINE, true, false, 0, NULL, NULL, NULL);

  printf("Found %d textline image components.\n", boxes->n);

  output_json.open(output_json_filename);
  output_json << "{\n";
  output_json << "  \"text_direction\": \"horizontal-lr\",\n";
  output_json << "  \"boxes\": [\n";

  l_int32 x, y, box_width, box_height;
  for (int i = 0; i < boxes->n; i++) {
    BOX* box = boxaGetBox(boxes, i, L_CLONE);
    boxGetGeometry(box, &x, &y, &box_width, &box_height);
    output_json << "    [" << x << "," << y << "," << x + box_width << "," << y + box_height << "]";
    if (i != (boxes->n - 1)) {
      output_json << ",";
    }
    output_json << "\n";
  }

	output_json << "  ],\n";
  output_json << "  \"script_detection\": false\n";
  output_json << "}";
  output_json.close();

  delete api;
  return 0;
}
