project('sdl', 'cpp')
add_project_arguments('-std=c++17', language : 'cpp')
gl = dependency('gl', method : 'auto')
sdl = dependency('sdl2')
glew = dependency('glew')
glm = dependency('glm')
src = [
		'src/camera.cpp',
		'src/display.cpp',
		'src/main.cpp',
		'src/mesh.cpp',
		'src/obj_loader.cpp',
		'src/shader.cpp',
		'src/stb_image.cpp',
		'src/texture.cpp',
		]
exc = executable('sdl', src, dependencies : [gl, sdl, glew, glm])
test('test', exc)
