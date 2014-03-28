
local source = {
[[
    #version 330
    layout(location = 0) in vec4 position;
    void main()
    {
       gl_Position = position;
    }
]],
[[
    #version 330
    out vec4 outputColor;
    void main()
    {
       outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
]]
}

function init()
    program = Program()

    vertexShader = Shader(GL_VERTEX_SHADER, source[1])
    fragmentShader = Shader(GL_FRAGMENT_SHADER, source[2])

    vertexShader:compile()
    fragmentShader:compile()

    program:addShader(vertexShader)
    program:addShader(fragmentShader)

    program:link()
end

