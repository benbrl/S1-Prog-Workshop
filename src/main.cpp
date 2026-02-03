#include <sil/sil.hpp>
#include "random.hpp"

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

void Disque_gif(sil::Image &image)
{
    int raduis = {100};
    float cercle = 2 * 3.14 * raduis;
    int center_x = image.width() / 2;
    int center_y = image.height() / 2;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (sqrt(std::pow((center_x - x), 2) + std::pow((center_y - y), 2)) < raduis)
            {
                image.pixel(x-50, y).r = 1.f;
                image.pixel(x-50, y).g = 1.f;
                image.pixel(x-50, y).b = 1.f;
            }
            else
            {
                image.pixel(x-50, y).r = 0.f;
                image.pixel(x-50, y).g = 0.f;
                image.pixel(x-50, y).b = 0.f;
            }
        }
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"};
        // TODO: modifier l'image
        image.save("output/pouet.png");
    }
    {
        sil::Image image{"images/logo.png"};
        keep_green_only(image);
        image.save("output/keep_green_only.png");
    }
    {
        sil::Image image{"images/logo.png"};
        black_and_white(image);
        image.save("output/black_and_white.png");
    }
    {
        sil::Image image{"images/logo.png"};
        negatif(image);
        image.save("output/negatif.png");
    }
    {
        sil::Image image{300 /*width*/, 200 /*height*/};
        degrade(image);
        image.save("output/degrade.png");
    }
    {
        sil::Image image{"images/logo.png"};
        negatif(image);
        image.save("output/negatif.png");
    }
    {
        sil::Image image{"images/logo.png"};
        miroir(image);
        image.save("output/miroir.png");
    }

    {
        sil::Image image{"images/logo.png"};
        noise_image(image);
        image.save("output/noise_image.png");
    }

    {
        sil::Image image{"images/logo.png"};
        rotate_90(image);
        image.save("output/rotate_90.png");
    }

    {
        sil::Image image{"images/logo.png"};
        RGB_split(image);
        image.save("output/RGB_split.png");
    }

    {
        sil::Image image{"images/photo.jpg"};
        Luminosite_eclaircir(image);
         Luminosite_assombrir(image);
        image.save("output/Luminosite.jpg");
    }

    {
        sil::Image image{"images/photo.jpg"};
        Luminosite_eclaircir(image);
        Luminosite_assombrir(image);
        image.save("output/Luminosite.jpg");
    }

    {
        sil::Image image{500 /*width*/, 500 /*height*/};
        Disque(image);
        image.save("output/Disque.jpg");
    }

    {
        sil::Image image{500 /*width*/, 500 /*height*/};
        Disque_gif(image);
        image.save("output/gif_disque/Disque_gif.jpg");

        //std format
    }
}