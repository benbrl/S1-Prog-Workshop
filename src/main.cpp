#include <sil/sil.hpp>
#include "random.hpp"
#include <iostream>
#include <format>
#include <numbers>
#include <algorithm>
#include <complex>

void keep_green_only(sil::Image &image)
{

    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
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

void degradeLab(sil::Image &image)
{
    for (int y = 0; y < image.height(); y++)
    {

        for (int x = 0; x < image.width(); x++)
        {
            float t = static_cast<float>(y / image.width());
            glm::vec3 color = glm::mix(
                glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                t);

            image.pixel(x, y) = color;
        }
    }
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

    {
        sil::Image image{500 /*width*/, 500 /*height*/};
        degradeLab(image);
        image.save("output/degradeLab.png");
    }
}