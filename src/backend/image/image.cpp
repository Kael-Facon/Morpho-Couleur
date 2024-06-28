#include "image.hh"

Image::Image(int width_, int height_)
{
    width = width_;
    height = height_;
    unsigned int size = width * height * 3;
    char_data = (unsigned char *)calloc(size + 1, sizeof(unsigned char));
    char_data[size] = '\0';
    data = std::vector<std::vector<Color>>(width,
                                           std::vector<Color>(height,
                                                              {0.0, 0.0, 0.0}));
    selected = std::vector<std::vector<bool>>(width,
                                              std::vector<bool>(height,
                                                                false));
}

Color Image::bg_color(Image *bg, Vector3 dir)
{
    float dirz = dir.z;
    if (dir.z < 0)
        dirz = -dirz;

    dir.normalize();
    int w = bg->width;
    int h = bg->height;
    int theta = static_cast<int>(acos(dir.y) * h / PI); // because dir is a unit vector
    int phi;
    if (dirz == 0)
        phi = w-1;
    else
        phi = static_cast<int>((atan(dir.x / dirz) + PI/2) * w / PI);

    return bg->data[phi][theta];
}

void Image::update_char_data(unsigned int i, unsigned int j) {
    unsigned int k = (j * width + i) * 3;
    char_data[k] = static_cast<unsigned char>(data[i][j].r * 255);
    char_data[k+1] = static_cast<unsigned char>(data[i][j].g * 255);
    char_data[k+2] = static_cast<unsigned char>(data[i][j].b * 255);
}

void Image::update_char_data(unsigned int i, unsigned int j, Color c) {
    unsigned int k = (j * width + i) * 3;
    char_data[k] = static_cast<unsigned char>(c.r * 255);
    char_data[k+1] = static_cast<unsigned char>(c.g * 255);
    char_data[k+2] = static_cast<unsigned char>(c.b * 255);
}

void Image::render_thread(Image *bg, int start, int end)
{
    for (unsigned int j = start; j < end; ++j)
    {
        for (unsigned int i = 0; i < width; ++i)
        {
            float k = static_cast<float>(i) / width;
            data[i][j] = Color(k, k, k);
            update_char_data(i, j);
        }
    }
}

void Image::render(Image *bg)
{
    const unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    int batchSize = height / numThreads; // Height is data size
    int start = 0;
    int end = 0;

    for (int i = 0; i < numThreads; ++i) {
        end = (i == numThreads - 1) ? height : start + batchSize;
        threads.emplace_back(&Image::render_thread, this, bg, start, end);
        start = end;
    }
    for (auto& t : threads)
        t.join();
}

void Image::save_as_ppm(const std::string& pathname)
{
    std::ofstream ofs;
    ofs.open(pathname, std::ifstream::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            Color c = data[i][j];
            ofs << static_cast<char>(255 * c.r)
                << static_cast<char>(255 * c.g)
                << static_cast<char>(255 * c.b);
        }
    }
    ofs.close();
}

Image *load_image(const std::string& path_name) {
    std::string line;
    std::ifstream ifs(path_name, std::ifstream::binary);
    if (!ifs.is_open()) {
        std::cerr << "Error Image: Unable to open file." << std::endl;
        return nullptr;
    }

    std::string magicNumber;
    int maxColor, width, height;
    ifs >> magicNumber >> width >> height >> maxColor;

    if (magicNumber != "P6" || maxColor != 255) {
        std::cerr << "Error Image: Invalid headers." << std::endl;
        return {};
    }
    ifs.get();

    Image image = Image(width, height);
    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i) {
            float r = ifs.get();
            float g = ifs.get();
            float b = ifs.get();
            image.data[i][j] = Color(r, g, b) / 255;
        }

    ifs.close();
    return new Image(image);
}