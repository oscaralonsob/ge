level = { 
    assets = {
       {type = "texture", id = "tank-image", path = "./assets/images/tank-panther-right.png"},
       {type = "texture", id = "truck-image", path = "./assets/images/truck-ford-right.png"},
       {type = "texture", id = "bullet-image", path = "./assets/images/bullet.png"},
       {type = "texture", id = "hero-image", path = "./assets/images/hero.png"},
       {type = "texture", id = "tilemap", path = "./assets/tilemaps/jungle.png"},
       {type = "font", id = "charriot-font", path = "./assets/fonts/charriot.ttf", size = 32},
       {type = "font", id = "charriot-font-mini", path = "./assets/fonts/charriot.ttf", size = 12},
    },

    units = {
        {
            name = "player",
            tag = "Player",
            group = "Ally",
            components = {
                transform = {
                    position = {x = 50.0, y = 50.0},
                    size = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                boxCollider = {
                    offset = {x = 0.0, y = 0.0},
                    size = {x = 32.0, y = 32.0},
                },
                sprite = {
                    texture = "hero-image"
                },
                rigidbody = {
                    velocity = {x = 100.0, y = 00.0},
                },
                cameraFollow = {
                },
                keyboardController = {
                    velocity = 100.0
                },
                health = {
                    max = 100,
                    current = 100
                },
                healthBar = {
                    font = "charriot-font-mini"
                },
                projectileEmitter = {
                    projectileVelocity = {x = 100.0, y = 100.0},
                    projectileFrequency = 1000,
                    projectileDuration = 10000,
                    hitDamage = 10,
                    isFriendly = 1,
                }
            }
        },
        {
            name = "enemyTank1",
            tag = "",
            group = "Enemies",
            components = {
                transform = {
                    position = {x = 50.0, y = 50.0},
                    size = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                sprite = {
                    texture = "tank-image"
                },
                rigidbody = {
                    velocity = {x = 0.0, y = 0.0},
                },
                boxCollider = {
                    offset = {x = 0.0, y = 0.0},
                    size = {x = 32.0, y = 32.0},
                },
                health = {
                    max = 100,
                    current = 100
                },
                healthBar = {
                    font = "charriot-font-mini"
                },
            }
        },
        {
            name = "enemyTank2",
            tag = "",
            group = "Enemies",
            components = {
                transform = {
                    position = {x = 10.0, y = 10.0},
                    size = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                sprite = {
                    texture = "tank-image"
                },
                rigidbody = {
                    velocity = {x = 0.0, y = 0.0},
                },
                boxCollider = {
                    offset = {x = 0.0, y = 0.0},
                    size = {x = 32.0, y = 32.0},
                },
                health = {
                    max = 100,
                    current = 100
                },
                healthBar = {
                    font = "charriot-font-mini"
                },
            }
        },
    }
}