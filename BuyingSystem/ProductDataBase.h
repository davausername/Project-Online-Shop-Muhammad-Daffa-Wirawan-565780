#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H

#include <vector>
#include <map>
#include <string>
#include "Products.h"

class ProductDatabase {
private:
    std::map<std::string, std::vector<Product>> categories;

public:
    ProductDatabase() {
        categories["Green Tech"] = {
            {"Solar Panels", "High-efficiency solar panels for home energy.", 1200.0},
            {"Home Wind Turbine", "Small wind turbine for household use.", 800.0},
            {"Smart Thermostat", "AI thermostat saving up to 40% electricity.", 250.0},
            {"Green AC", "Eco-friendly AC system.", 1500.0},
            {"Smart Sprinklers", "Smart sprinklers that save up to 60% water.", 300.0}
        };

        categories["Drones"] = {
            {"Camera Drone", "4K drone with stabilizer.", 600.0},
            {"Military Drone", "Heavy-duty surveillance drone.", 2500.0},
            {"Adventure Drone", "Durable drone for extreme travel.", 1200.0},
            {"Winter Drone", "Cold-resistant drone.", 900.0},
            {"Delivery Drone", "Autonomous delivery drone.", 2000.0}
        };

        categories["Books"] = {
            {"Atomic Habits", "A book about building better habits.", 15.0},
            {"Surrounded By Idiots", "Understanding personality types.", 20.0},
            {"Think and Grow Rich", "Classic self-development book.", 18.0},
            {"The Psychology of Money", "Money behavior explained.", 22.0},
            {"The Intelligent Investor", "Investment principles.", 25.0}
        };

        categories["Classy Laptops"] = {
            {"Apple MacBook Pro", "High-performance laptop with M1 chip.", 2000.0},
            {"HP Spectre x360", "Convertible laptop with touch screen.", 1500.0},
            {"Dell XPS 13", "Compact and powerful laptop.", 1300.0},
            {"Microsoft Surface Laptop", "Lightweight laptop with touch screen.", 1400.0},
            {"Nokia Laptop", "High-efficiency laptop.", 700.0}
        };

        categories["Appliances"] = {
            {"LED Light", "Energy-efficient LED light bulb.", 15.0},
            {"Smart Refrigerator", "Energy-saving smart fridge.", 1200.0},
            {"Microwave Oven", "Compact microwave oven.", 150.0},
            {"Air Conditioner", "Energy-efficient air conditioner.", 500.0},
            {"Washing Machine", "High-efficiency washing machine.", 700.0}
        };

        categories["German Cars"] = {
            {"BMW 3 Series", "Luxury sedan with sporty performance.", 41000.0},
            {"Audi A4", "Premium sedan with advanced technology.", 39000.0},
            {"Mercedes-Benz C-Class", "Elegant sedan with luxurious features.", 42000.0},
            {"Volkswagen Golf", "Compact car with efficient performance.", 25000.0},
            {"Porsche 911", "High-performance sports car.", 99000.0}
        };

        categories["German Tech"] = {
            {"Siemens Home Appliance", "Energy-efficient home appliance.", 800.0},
            {"Bosch Power Tool", "Durable and powerful tool.", 300.0},
            {"SAP Software Suite", "Enterprise software solutions.", 5000.0},
            {"Adidas Smartwatch", "Fitness smartwatch with advanced features.", 200.0},
            {"Bayer Health Device", "Health monitoring device.", 150.0}
        };

        categories["German Books"] = {
            {"Panzer Commander", "A classic account from a German tank commander.", 15.0},
            {"Mein Kampf", "Infamous as Hitler's autobiographical manifesto.", 20.0},
            {"Berlin Alexanderplatz by Döblin", "Modernist novel set in Berlin.", 14.0},
            {"All Quiet on the Western Front by Remarque", "World War I novel.", 10.0},
            {"The Magic Mountain by Mann", "Philosophical novel.", 18.0}
        };

        categories["German Appliances"] = {
            {"Miele Washing Machine", "High-efficiency German washing machine.", 900.0},
            {"Bosch Dishwasher", "Quiet and efficient dishwasher.", 700.0},
            {"Siemens Refrigerator", "Energy-saving German refrigerator.", 1200.0},
            {"AEG Oven", "Advanced cooking oven.", 800.0},
            {"Liebherr Freezer", "High-capacity German freezer.", 1000.0}
        };
    }

    // Safe access
    const std::vector<Product>& getCategory(const std::string& name) const {
        return categories.at(name);
    }

    bool hasCategory(const std::string& name) const {
        return categories.find(name) != categories.end();
    }

    std::vector<std::string> getCategoryNames() const {
        std::vector<std::string> names;
        for (const auto& c : categories)
            names.push_back(c.first);
        return names;
    }
};

#endif
