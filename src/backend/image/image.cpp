#include <algorithm>
#include "image.hh"

static float aspect_ratio = 16.0f / 9.0f;
static int default_width = 1600;
static int default_height = 900; //static_cast<int>(static_cast<float>(default_width) / aspect_ratio);

Image::Image()
{
    width = default_width;
    height = default_height;
    unsigned int size = width * height * 3;
    char_data = (unsigned char *)calloc(size + 1, sizeof(unsigned char));
    char_data[size] = '\0';
    data = std::vector<std::vector<Color>>(width,
                                           std::vector<Color>(height,
                                                              {0.0, 0.0, 0.0}));
}

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

void Image::update_char_data()
{
    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
            update_char_data(i , j);
}

void Image::update_char_data(unsigned char *data_, bool gray)
{
    if (gray)
        for (unsigned int j = 0; j < height; ++j)
            for (unsigned int i = 0; i < width; ++i)
            {
                char_data[(i + j * width) * 3] = data_[(i + j * width)];
                char_data[(i + j * width) * 3 + 1] = data_[(i + j * width)];
                char_data[(i + j * width) * 3 + 2] = data_[(i + j * width)];
            }

    else
        for (unsigned int j = 0; j < height; ++j)
            for (unsigned int i = 0; i < width; ++i)
            {
                char_data[(i + j * width) * 3] = data_[(i + j * width) * 3];
                char_data[(i + j * width) * 3 + 1] = data_[(i + j * width) * 3 + 1];
                char_data[(i + j * width) * 3 + 2] = data_[(i + j * width) * 3 + 2];
            }
}

void Image::update_color_data()
{
    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
        {
            data.at(i).at(j).r = char_data[(i + j * width) * 3] / 255.f;
            data.at(i).at(j).g = char_data[(i + j * width) * 3 + 1] / 255.f;
            data.at(i).at(j).b = char_data[(i + j * width) * 3 + 2] / 255.f;
        }
}

Color rgb_to_hsv(Color c) {
    float max_color = std::max(std::max(c.r, c.g), c.b);
    float min_color = std::min(std::min(c.r, c.g), c.b);
    float max_min = max_color - min_color;
    Color hsv_c = Color();
    if (max_min == 0)
        hsv_c.r = 0; // h
    else if (max_color == c.r)
        hsv_c.r = (c.g-c.b)/max_min; // h
    else if (max_color == c.g)
        hsv_c.r = 2.0f + (c.b-c.r)/max_min; // h
    else // (max_color == c.b)
        hsv_c.r = 4.0f + (c.r-c.g)/max_min; // h
    hsv_c.r *= 60; // h

    if (hsv_c.r < 0)
        hsv_c.r += 360;
    if (hsv_c.r >= 360)
        hsv_c.r -= 360;

    hsv_c.g = 0; // s
    if (max_color != 0)
        hsv_c.g = 1 - min_color / max_color; // s
    hsv_c.b = max_color; // v

    return hsv_c;
}

Color hsv_to_rgb(Color c) {
    Color rgb_c{};
    int hi = static_cast<int>(c.r/60) % 6; // h
    float f = c.r/60 - hi; // h
    float l = c.b * (1 - c.g); // v and s
    float m = c.b * (1 - f * c.g); // v and s
    float n = c.b * (1 - (1 - f) * c.g); // v and s
    switch (hi) {

        case 0:
            rgb_c = Color(c.b, n, l); // v
            break;
        case 1:
            rgb_c = Color(m, c.b, l); // v
            break;
        case 2:
            rgb_c = Color(l, c.b, n); // v
            break;
        case 3:
            rgb_c = Color(l, m, c.b); // v
            break;
        case 4:
            rgb_c = Color(n, l, c.b); // v
            break;
        default:
            rgb_c = Color(c.b, l, m); // v
            break;
    }

    return rgb_c;
}

void Image::convert_thread(IMAGE_TYPE new_type, int start, int end)
{
    for (unsigned int j = start; j < end; ++j)
    {
        for (unsigned int i = 0; i < width; ++i)
        {
            if (new_type == RGB) {
                if (image_type == HSV)
                    data[i][j] = rgb_to_hsv(data[i][j]);
                else { // GRAY
                    auto gray = (data[i][j].r + data[i][j].g + data[i][j].b) / 3.0f;
                    data[i][j] = Color(gray,gray,gray);
                }
            }

            if (new_type == HSV) {
                data[i][j] = hsv_to_rgb(data[i][j]);
                if (image_type == GRAY) {
                    auto gray = (data[i][j].r + data[i][j].g + data[i][j].b) / 3.0f;
                    data[i][j] = Color(gray,gray,gray);
                }
            }

            if (new_type == GRAY) {
                if (image_type == HSV)
                    data[i][j] = rgb_to_hsv(data[i][j]);
                // NOTHING TO DO FOR GRAY TO RGB
            }
            image_type = new_type;
            update_char_data(i, j);
        }
    }
}

void Image::convert_image(IMAGE_TYPE new_type)
{
    if (new_type == image_type || new_type == NONE)
        return;

    if (image_type == GRAY && new_type == RGB){
        image_type = RGB;
        return;
    }

    const unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    int batchSize = height / numThreads; // Height is data size
    int start = 0;
    int end = 0;

    for (int i = 0; i < numThreads; ++i) {
        end = (i == numThreads - 1) ? height : start + batchSize;
        threads.emplace_back(&Image::convert_thread, this, new_type, start, end);
        start = end;
    }
    for (auto& t : threads)
        t.join();
}

std::vector<std::vector<unsigned int>> Image::get_histogram()
{
    std::vector<std::vector<unsigned int>> histogram(
            3,
            std::vector<unsigned int>(255, 0.0)
    );
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            histogram[0][static_cast<int>(data[i][j].r * 255)]++; // 0 - 255
            histogram[1][static_cast<int>(data[i][j].g * 255)]++; // 0 - 255
            histogram[2][static_cast<int>(data[i][j].b * 255)]++; // 0 - 255
        }
    }
    return histogram;
}

void Image::to_gray()
{
    to_gray(0.25, 0.6, 0.15);
}

void Image::to_gray(float r_ratio, float g_ratio, float b_ratio)
{
    float total_ratio = r_ratio + g_ratio + b_ratio;
    r_ratio /= total_ratio;
    g_ratio /= total_ratio;
    b_ratio /= total_ratio;

    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i)
            data[i][j].to_gray(r_ratio, g_ratio, b_ratio);
}

uint8_t* Image::get_channel(IMAGE_CHANNEL chan)
{
    if (chan > IMAGE_CHANNEL::B)
        return nullptr;

    uint8_t *channel = (uint8_t *) malloc(width * height * sizeof(uint8_t)); // sizeof == 1

    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i)
            channel[i + j * width] = char_data[(i + j * width) * 3 + (int) chan];

    return channel;
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

    std::vector<std::vector<Color>> data_(width,
                                           std::vector<Color>(height,
                                                              {0.0, 0.0, 0.0}));
    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i) {
            float r = ifs.get();
            float g = ifs.get();
            float b = ifs.get();
            data_[i][j] = Color(r, g, b) / 255;
        }
    ifs.close();

    Image image = Image();
    float diff = static_cast<float>(height) / image.height;
    for (int j = 0; j < image.height; ++j)
        for (int i = 0; i < image.width; ++i) {
            image.data[i][j] = data_[i * diff][j * diff];
            image.update_char_data(i, j);
        }

    return new Image(image);
}