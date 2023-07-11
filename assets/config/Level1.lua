level = { 
    assets = {
       {type = "texture", id = "tank-image", path = "./assets/images/tank-panther-right.png"},
       {type = "texture", id = "truck-image", path = "./assets/images/truck-ford-right.png"},
       {type = "texture", id = "bullet-image", path = "./assets/images/bullet.png"},
       {type = "texture", id = "hero-image", path = "./assets/images/hero.png"},
       {type = "texture", id = "tilemap", path = "./assets/tilemaps/jungle.png"},
       {type = "texture", id = "charriot-font", path = "./assets/fonts/charriot.ttf"},
       {type = "texture", id = "charriot-font-mini", path = "./assets/fonts/charriot.ttf"},
    }

     entities = {
        name = "Player" -- This is ignored but helps a lot
        tag = "player",
        components = {
            transform = {
                position = { x = 750, y = 450 },
                scale = { x = 1.0, y = 1.0 },
                rotation = 0.0,
            },
            rigidbody = {
                velocity = { x = 0.0, y = 0.0 }
            },
            sprite = {
                texture_asset_id = "hero-image",
                width = 32,
                height = 32,
                z_index = 6,
                fixed = false,
                src_rect_x = 0,
                src_rect_y = 0
            },
            boxcollider = {
                width = 32,
                height = 25,
                offset = { x = 0, y = 5 }
            },
            health = {
                health_percentage = 100
            },
            projectile_emitter = {
                projectile_velocity = { x = 200, y = 200 },
                projectile_duration = 10, -- seconds
                repeat_frequency = 0, -- seconds
                hit_percentage_damage = 10,
                friendly = true
            },
            keyboard_controller = {
                up_velocity = { x = 0, y = -30 },
                right_velocity = { x = 30, y = 0 },
                down_velocity = { x = 0, y = 30 },
                left_velocity = { x = -30, y = 0 }
            },
            camera_follow = {
                follow = true
            }
        }
    },
}