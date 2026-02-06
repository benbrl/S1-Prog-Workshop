//  ____  _   _ ____  _____ ____
// / ___|| | | |  _ \| ____|  _ \                      
// \___ \| | | | |_) |  _| | |_) |
//  ___) | |_| |  __/| |___|  _ <
// |____/ \___/|_|  _|_____|_|_\_\_  _   _  ___  ____
// \ \      / / _ \|  _ \| |/ / ___|| | | |/ _ \|  _ \ 
//  \ \ /\ / / | | | |_) | ' /\___ \| |_| | | | | |_) |
//   \ V  V /| |_| |  _ <| . \ ___) |  _  | |_| |  __/
//    \_/\_/  \___/|_| \_\_|\_\____/|_| |_|\___/|_|

#include <sil/sil.hpp>
#include "random.hpp"
#include <iostream>
#include <format>
#include <numbers>
#include <algorithm>
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>

void keep_green_only(sil::Image &image)
{

    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void keep_red_only(sil::Image &image)
{

    for (glm::vec3 &color : image.pixels())
    {
        color.g = 0.f;
        color.b = 0.f;
    }
}
void swap_channel(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.b, color.r);
    }
}

void black_and_white(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float moyenne = (color.r * 0.30f + color.g * 0.59f + color.b * 0.11f) / 3;
        color.r = moyenne;
        color.g = moyenne;
        color.b = moyenne;
    }
}

void negatif(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
}

void degrade(sil::Image &image)

{
    for (int x{0}; x < image.width(); x++)
    {
        float pixel = static_cast<float>(x) / image.width();
        glm::vec3 vecteur{pixel};
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = vecteur;
        }
    }
}

void miroir(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.width() - 1 - x, y));
        }
    }
}

void noise_image(sil::Image &image)
{

    for (int i = 0; i < random_int(image.width() * 20, image.width() * 40); i++)
    {
        int random_x = random_int(0, image.width());
        int random_y = random_int(0, image.height());

        glm::vec3 pixel{random_float(0, 1), random_float(0, 1), random_float(0, 1)};
        image.pixel(random_x, random_y) = pixel;
    }
}

void rotate_90(sil::Image &image)
{

    sil::Image image_new{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image_new.pixel(image.height() - y - 1, x) = image.pixel(x, y);
        }
    }

    image = image_new;
}

void RGB_split(sil::Image &image)
{
    int decalage = {30};

    sil::Image image_new{image.width(), image.height()};
    for (int x{0}; x < image.width() - 1; x++)
    {
        for (int y{0}; y < image.height() - 1; y++)
        {
            if (x <= decalage)
            {
                image_new.pixel(x, y).r = 0.f;
                image_new.pixel(x, y).g = image.pixel(x, y).g;
                image_new.pixel(x, y).b = image.pixel(x + decalage, y).b;
            }
            else if (x >= image.width() - decalage)
            {
                image_new.pixel(x, y).r = image.pixel(x - decalage, y).r;
                image_new.pixel(x, y).g = image.pixel(x, y).g;
                image_new.pixel(x, y).b = 0.f;
            }
            else
            {
                image_new.pixel(x, y).r = image.pixel(x - decalage, y).r;
                image_new.pixel(x, y).g = image.pixel(x, y).g;
                image_new.pixel(x, y).b = image.pixel(x + decalage, y).b;
            }
        }
    }
    image = image_new;
}

void Luminosite_eclaircir(sil::Image &image)
{
    const float puissance = {0.3f};

    for (glm::vec3 &color : image.pixels())
    {
        color = glm::pow(color, glm::vec3{puissance});
    }
}

void Luminosite_assombrir(sil::Image &image)
{
    const float puissance = 2.0f;

    for (glm::vec3 &color : image.pixels())
    {
        color = glm::pow(color, glm::vec3{puissance});
    }
}

void Disque(sil::Image &image)
{
    int raduis = {100};
    float cercle = 2 * 3.14 * raduis;
    int center_x = image.width() / 2;
    int center_y = image.height() / 2;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            if (center_x > 0 && center_x < image.width())
            {
                if (sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) < raduis)
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
                else
                {
                    image.pixel(x, y).r = 0.f;
                    image.pixel(x, y).g = 0.f;
                    image.pixel(x, y).b = 0.f;
                }
            }
        }
    }
}

void cercle(sil::Image &image)
{
    int raduis = {100};
    int thickness = {10};
    int center_x = image.width() / 2;
    int center_y = image.height() / 2;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) < raduis && sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) > raduis - thickness)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
            else
            {
                image.pixel(x, y).r = 0.f;
                image.pixel(x, y).g = 0.f;
                image.pixel(x, y).b = 0.f;
            }
        }
    }
}

void Disque_gif(sil::Image &image, int count)
{
    int raduis = {100};
    float cercle = 2 * 3.14 * raduis;
    int center_x = count;
    int center_y = image.height() / 2;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            if (sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) < raduis)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
            else
            {
                image.pixel(x, y).r = 0.f;
                image.pixel(x, y).g = 0.f;
                image.pixel(x, y).b = 0.f;
            }
        }
    }
}

void new_cercle(sil::Image &image, int center_x, int center_y, int raduis, int thickness)
{

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) < raduis && sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) > raduis - thickness)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

void Rosace(sil::Image &image)
{
    int raduis = {100};
    float cercle = 2 * 3.14 * raduis;
    int center_x = image.width() / 2;
    int center_y = image.height() / 2;

    int nb_rosace = 10;

    // postion_rosace

    float angle = 360 / nb_rosace;

    for (int i = {0}; i < nb_rosace; i++)
    {
        float angle_rad = (3.14 / 180) * angle * i;
        float position_x_rosace = cos(angle_rad) * raduis + center_x;
        float position_y_rosace = sin(angle_rad) * raduis + center_y;
        new_cercle(image, position_x_rosace, position_y_rosace, raduis, 10);
    }

    new_cercle(image, center_x, center_y, raduis, 10);
}

void Mosaique(sil::Image &image)
{
    int nb_repetition = 5;

    int new_image_width = image.width() * nb_repetition;
    int new_image_height = image.height() * nb_repetition;

    sil::Image new_image{new_image_width, new_image_height};

    for (int i = {0}; i < nb_repetition; i++)
    {

        for (int j = {0}; j < nb_repetition; j++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                int new_x = x + image.width() * j;
                for (int y{0}; y < image.height(); y++)
                {

                    int new_y = y + image.height() * i;
                    new_image.pixel(new_x, new_y) = image.pixel(x, y);
                }
            }
        }
    }

    image = new_image;
}

void Mosaique_miroir(sil::Image &image)
{
    int nb_repetition = 5;

    int new_image_width = image.width() * nb_repetition;
    int new_image_height = image.height() * nb_repetition;

    sil::Image new_image{new_image_width, new_image_height};

    for (int i = {0}; i < nb_repetition; i++)
    {
        for (int j = {0}; j < nb_repetition; j++)
        {
            for (int y = {0}; y < image.height(); y++)
            {
                for (int x = {0}; x < image.width(); x++)
                {
                    int image_x = x;
                    int image_y = y;

                    if (j % 2 == 1)
                    {
                        image_x = image.width() - 1 - x;
                    }

                    if (i % 2 == 1)
                    {
                        image_y = image.height() - 1 - y;
                    }

                    int new_x = x + j * image.width();
                    int new_y = y + i * image.height();

                    new_image.pixel(new_x, new_y) = image.pixel(image_x, image_y);
                }
            }
        }
    }

    image = new_image;
}

void Glitch(sil::Image &image)
{
    int iteration = random_int(10, 30);

    /// faire deux rectangles et les swaps normalement la team c'est ça
    for (int j = {0}; j < iteration; j++)
    {

        int height = random_int(1, 20);
        int width = random_int(1, 40);
        int random_x = random_int(1, image.height() - height);
        int random_y = random_int(1, image.width() - width);

        if (random_x + width < image.width() - width && random_y + height < image.height() - height)
        {
            for (int x{0}; x < width; x++)
            {
                for (int y{0}; y < height; y++)
                {
                    std::swap(image.pixel((random_x + x), (random_y + y)), image.pixel(random_x + x + width, random_x + y + height));
                }
            }
        }
    }
}

float brightness(glm::vec3 const &color)
{
    float moyenne = color.r * 0.2126f + color.g * 0.7152f + color.b * 0.0722f;
    return moyenne;
}

void Tri_pixels(sil::Image &image)
{
    int random = random_int(300, 400);

    for (int i = 0; i < random; i++)
    {

        int size_x = random_int(20, 45);
        int x_begin = random_int(0, image.width() - size_x);
        // int x_end = random_int(10, image.width() - size_x); /// clacluel le. omvre dnas le talbeau

        // on vuet jsute savir usr quelle ligne le u vuet etre
        int y = random_int(10, image.height());

        std::vector<glm::vec3> vecteur;
        for (int x = x_begin; x < size_x + x_begin; x++)
        {
            glm::vec3 pixel = image.pixel(x, y);
            vecteur.push_back(pixel);
        }

        // std::cout << vecteur.size() << std::endl;

        std::sort(vecteur.begin(), vecteur.end(),
                  [](glm::vec3 const &color1, glm::vec3 const &color2)
                  {
                      // std::cout << "bonjour" << std::endl;
                      return brightness(color1) < brightness(color2);
                  });

        for (int x = x_begin; x < size_x + x_begin; x++)
        {
            image.pixel(x, y) = vecteur.at(x - x_begin);
        }
    }
}

void fractal(sil::Image &image)
{
    int iteration = 19;
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            float xx = static_cast<float>(x * 4) / image.width() - 2;
            float yy = static_cast<float>(y * 4) / image.height() - 2;
            // std::cout << xx << ' ' << yy << std::endl;
            std::complex<float> z{0.f, 0.f};
            std::complex<float> c{xx, yy};
            bool is_fractal = false;
            float color;
            for (int i{0}; i < iteration; ++i)
            {
                z = z * z + c;
                color = static_cast<float>(i * 1) / 20;
                std::cout << color << std::endl;
                if (std::abs(z) > 2)
                {
                    is_fractal = true;

                    break;
                }
            }

            if (is_fractal)
            {

                image.pixel(x, y) = glm::vec3{color};
            }
            else
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

void degradeCouleur(sil::Image &image)
{
    float degrade;
    for (int y = 0; y < image.height(); y++)
    {

        for (int x = 0; x < image.width(); x++)
        {
            degrade = static_cast<float>(x) / static_cast<float>(image.width());
            glm::vec3 color = glm::mix(
                glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                degrade);

            image.pixel(x, y) = color;
        }
    }
}

struct Lab
{
    float L;
    float a;
    float b;
};

// copie depuis le site https://bottosson.github.io/posts/oklab/
struct RGB
{
    float r;
    float g;
    float b;
};

Lab linear_rgb_to_oklab(RGB color)
{
    float l = 0.4122214708f * color.r + 0.5363325363f * color.g + 0.0514459929f * color.b;
    float m = 0.2119034982f * color.r + 0.6806995451f * color.g + 0.1073969566f * color.b;
    float s = 0.0883024619f * color.r + 0.2817188376f * color.g + 0.6299787005f * color.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_,
        1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_,
        0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_,
    };
}

RGB oklab_to_linear_rgb(Lab color)
{
    float l_ = color.L + 0.3963377774f * color.a + 0.2158037573f * color.b;
    float m_ = color.L - 0.1055613458f * color.a - 0.0638541728f * color.b;
    float s_ = color.L - 0.0894841775f * color.a - 1.2914855480f * color.b;

    float l = l_ * l_ * l_;
    float m = m_ * m_ * m_;
    float s = s_ * s_ * s_;

    return {
        +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
        -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
        -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

void degradeOKLAB(sil::Image &image)
{

    float color_g = random_float(0, 1);
    float color_b = random_float(0, 1);
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            float degrade = static_cast<float>(x) / image.width();

            RGB color = {degrade, color_g, color_b};
            Lab lab = linear_rgb_to_oklab(color);

            if (color.r <= 0.0031308)
            {
                color.r = color.r * 12.92;
            }
            else
            {
                color.r = 1.055 * std::pow(color.r, 1 / 2.4) - 0.055;
            }

            if (color.g <= 0.0031308)
            {
                color.g = 1.055 * std::pow(color.g, 1 / 2.4) - 0.055;
            }
            if (color.b <= 0.0031308)
            {
                color.b = 1.055 * std::pow(color.b, 1 / 2.4) - 0.055;
            }
            image.pixel(x, y).r = color.r;
            image.pixel(x, y).g = color.g;
            image.pixel(x, y).b = color.b;
        }
    }
}

void Tramage(sil::Image &image)
{

    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {-0.5, 0, -0.375, 0.125},
        {0.25, -0.25, 0.375, -0.125},
        {-0.3125, 0.1875, -0.4375, 0.0625},
        {0.4375, -0.0625, 0.3125, -0.1875},
    };

    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            glm::vec3 orig_color = image.pixel(x, y);
            glm::vec3 color_result;

            float moyenne = (orig_color.r + orig_color.g + orig_color.b) / 3.0f;
            float bayer_value = bayer_matrix_4x4[y % bayer_n][x % bayer_n];
            float output_color = moyenne + bayer_value;

            if (output_color < 0.5f)
            {
                color_result = glm::vec3(0.f);
            }
            else
            {
                color_result = glm::vec3(1.f);
            }
            image.pixel(x, y) = color_result;
        }
    }
}

void photo_faible_contraste(sil::Image &image)
{

    float min_brightness{1};
    float max_brightness{0};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            glm::vec3 color = image.pixel(x, y);

            float current_brightness = color.r * 0.2126f + color.g * 0.7152f + color.b * 0.0722f;

            max_brightness = std::max(max_brightness, current_brightness);
            min_brightness = std::min(min_brightness, current_brightness);
        }
    }

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            glm::vec3 &color = image.pixel(x, y);

            color = (color - min_brightness) / (max_brightness - min_brightness);

            // image.pixel(x, y) = color;
        }
    }
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void Vortex(sil::Image &image)
{
    glm::vec2 point;
    glm::vec2 center_of_rotation = glm::vec2(image.width() / 2, image.height() / 2);

    // float angle = 20 * 3.14 / 180;

    float radian = 10;

    sil::Image image_new{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            point = {x, y};
            float distance = glm::distance(center_of_rotation, point);
            // float angle = (distance *radian);
            float angle = (distance / radian);
            glm::vec2 nvpt = rotated(point, center_of_rotation, angle);
            if (nvpt.x >= 0 && nvpt.x < image.width() && nvpt.y < image.height() && nvpt.y >= 0)
            {

                image_new.pixel(x, y) = image.pixel(nvpt.x, nvpt.y);
            }
            else
            {
                image_new.pixel(x, y) = glm::vec3(0.0f);
            }
        }
    }

    image = image_new;
}

void Convolutions_sharpness(sil::Image &image)
{
    float convolution_3x3[3][3] = {
        {0.0, -1.0, 0.0},
        {-1.0, 5.0, -1.0},
        {0.0, -1.0, 0.0},
    };

    sil::Image image_new{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x >= 1 && x < image.width() - 1 && y >= 1 && y < image.height() - 1)
            {
                glm::vec3 pixel{0.0};
                for (int x_matrice{-1}; x_matrice <= 1; x_matrice++)
                {
                    for (int y_matrice{-1}; y_matrice <= 1; y_matrice++)
                    {

                        pixel = pixel + convolution_3x3[x_matrice + 1][y_matrice + 1] * image.pixel(x + x_matrice, y + y_matrice);
                    }
                }

                image_new.pixel(x, y) = pixel;
            }
            else
            {
                image_new.pixel(x, y) = image.pixel(x, y);
            }
        }
    }

    image = image_new;
}

void Convolutions_blur(sil::Image &image)
{

    sil::Image image_new{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x >= 1 && x < image.width() - 1 && y >= 1 && y < image.height() - 1)
            {

                glm::vec3 pixel{0.0};
                for (int x_matrice{-1}; x_matrice <= 1; x_matrice++)
                {
                    for (int y_matrice{-1}; y_matrice <= 1; y_matrice++)
                    {

                        pixel = pixel + image.pixel(x + x_matrice, y + y_matrice);
                    }
                }

                image_new.pixel(x, y) = pixel / 9.0f;
            }
            else
            {
                image_new.pixel(x, y) = image.pixel(x, y);
            }
        }
    }

    image = image_new;
}

void Convolutions_outline(sil::Image &image)
{
    float convolution_3x3[3][3] = {
        {-1.0, -1.0, -1.0},
        {-1.0, 8.0, -1.0},
        {-1.0, -1.0, -1.0},
    };

    sil::Image image_new{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x >= 1 && x < image.width() - 1 && y >= 1 && y < image.height() - 1)
            {
                glm::vec3 pixel{0.0};
                for (int x_matrice{-1}; x_matrice <= 1; x_matrice++)
                {
                    for (int y_matrice{-1}; y_matrice <= 1; y_matrice++)
                    {

                        pixel = pixel + convolution_3x3[x_matrice + 1][y_matrice + 1] * image.pixel(x + x_matrice, y + y_matrice);
                    }
                }

                image_new.pixel(x, y) = pixel;
            }
            else
            {
                image_new.pixel(x, y) = image.pixel(x, y);
            }
        }
    }

    image = image_new;
}

void Convolutions_emboss(sil::Image &image)
{
    float convolution_3x3[3][3] = {
        {-2.0, -1.0, 0.0},
        {-1.0, 1.0, 1.0},
        {0.0, 1.0, 2.0},
    };

    sil::Image image_new{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x >= 1 && x < image.width() - 1 && y >= 1 && y < image.height() - 1)
            {
                glm::vec3 pixel{0.0};
                for (int x_matrice{-1}; x_matrice <= 1; x_matrice++)
                {
                    for (int y_matrice{-1}; y_matrice <= 1; y_matrice++)
                    {

                        pixel = pixel + convolution_3x3[x_matrice + 1][y_matrice + 1] * image.pixel(x + x_matrice, y + y_matrice);
                    }
                }

                image_new.pixel(x, y) = pixel;
            }
            else
            {
                image_new.pixel(x, y) = image.pixel(x, y);
            }
        }
    }

    image = image_new;
}

int main()
{
    // {
    //     sil::Image image{"images/logo.png"};
    //     // TODO: modifier l'image
    //     image.save("output/pouet.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     keep_green_only(image);
    //     image.save("output/keep_green_only.png");
    // }
    //     {
    //     sil::Image image{"images/logo.png"};
    //    keep_red_only(image);
    //     image.save("output/keep_red_only.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     black_and_white(image);
    //     image.save("output/black_and_white.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     negatif(image);
    //     image.save("output/negatif.png");
    // }
    // {
    //     sil::Image image{300 /*width*/, 200 /*height*/};
    //     degrade(image);
    //     image.save("output/degrade.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     negatif(image);
    //     image.save("output/negatif.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     miroir(image);
    //     image.save("output/miroir.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     noise_image(image);
    //     image.save("output/noise_image.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     rotate_90(image);
    //     image.save("output/rotate_90.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     RGB_split(image);
    //     image.save("output/RGB_split.png");
    // }

    // {
    //     sil::Image image{"images/photo.jpg"};
    //     Luminosite_eclaircir(image);
    //     Luminosite_assombrir(image);
    //     image.save("output/Luminosite.jpg");
    // }

    // {
    //     sil::Image image{"images/photo.jpg"};
    //     Luminosite_eclaircir(image);
    //     Luminosite_assombrir(image);
    //     image.save("output/Luminosite.jpg");
    // }

    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     Disque(image);
    //     image.save("output/Disque.jpg");
    // }

    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     cercle(image);
    //     image.save("output/cercle.png");
    // }

    // {
    //     int square_size = 500;
    //     sil::Image image{square_size /*width*/, square_size /*height*/};

    //     for (int count = {0}; count < square_size; count++)
    //     {
    //         Disque_gif(image, count);
    //         std::string path = std::format("output/gif_disque/Disque_gif_{}.png", count);
    //         image.save(path);
    //     }
    // }

    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     Rosace(image);
    //     image.save("output/Rosace.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Mosaique(image);
    //     image.save("output/Mosaique.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Mosaique_miroir(image);
    //     image.save("output/Mosaique_miroir.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Glitch(image);
    //     image.save("output/Glitch.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Tri_pixels(image);
    //     image.save("output/Tri_pixels.png");
    // }

    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     fractal(image);
    //     image.save("output/fractal.png");
    // }

    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     degradeCouleur(image);
    //     image.save("output/degradeLab.png");
    // }

    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     degradeOKLAB(image);
    //     image.save("output/degradeOKLAB.png");
    // }

    // {
    //     sil::Image image{"images/photo.jpg"};
    //     Tramage(image);
    //     image.save("output/Tramage.png");
    // }

    // {
    //     sil::Image image{"images/photo_faible_contraste.jpg"};
    //     photo_faible_contraste(image);
    //     image.save("output/photo_faible_contraste.png");
    // }

    // {
    //     sil::Image image{"images/logo.png"};
    //     Vortex(image);
    //     image.save("output/Vortex.png");
    // }

    {
        sil::Image image{"images/logo.png"};
        Convolutions_blur(image);
        image.save("output/Convolutions.png");
    }
    {
        sil::Image image{"images/logo.png"};
        Convolutions_sharpness(image);
        image.save("output/Convolutions_sharpness.png");
    }

    {
        sil::Image image{"images/logo.png"};
        Convolutions_outline(image);
        image.save("output/Convolutions_outline.png");
    }

    {
        sil::Image image{"images/logo.png"};
        Convolutions_emboss(image);
        image.save("output/Convolutions_emboss.png");
    }
}