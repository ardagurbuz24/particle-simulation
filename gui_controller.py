import ctypes
import customtkinter as ctk

particle_lib = ctypes.CDLL("./particle_lib.so")
particle_lib.set_gravity.argtypes = [ctypes.c_float]

ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("blue")

class ParticleController(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("Particle Engine")
        self.geometry("300x300")

        self.label = ctk.CTkLabel(self, text="Physics Settings", font=("Arial", 23))
        self.label.pack(pady=20)

        self.gravity_label = ctk.CTkLabel(self, text="Set Gravity")
        self.gravity_label.pack()
        
        self.gravity_slider = ctk.CTkSlider(self, from_=0, to=1, command=self.update_gravity)
        self.gravity_slider.pack(pady=20)
        self.gravity_slider.set(0.15)

        self.reset_button = ctk.CTkButton(self, text="Explode Particles", command=self.explode_particles)
        self.reset_button.pack(pady=20)

        self.update_loop()

    def update_loop(self):
        particle_lib.run_frame()
        self.after(16, self.update_loop) # 60 fps

    def update_gravity(self, value):
        print(f"New Gravity: {value}")
        particle_lib.set_gravity(ctypes.c_float(value))

    def explode_particles(self):
        print("Particles Exploded")
        particle_lib.trigger_explosion()

    

if __name__ == "__main__":
    particle_lib.init_all()

    app = ParticleController()
    app.mainloop()