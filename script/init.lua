
local source = {
[[
    attribute vec4 position;
    void main()
    {
       gl_Position = position;
    }
]],
[[
    void main()
    {
       gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
]]
}

function init()
    program = Program()

    local vertexShader = Shader(GL_VERTEX_SHADER, source[1])
    local fragmentShader = Shader(GL_FRAGMENT_SHADER, source[2])

    vertexShader:compile()
    fragmentShader:compile()

    program:addShader(vertexShader)
    program:addShader(fragmentShader)

    program:link()

    buffer = TrianglesBuffer(program:getAttribLocation("position"))

    buffer:setPoint(0, 0.75, 0.75, 0, 1)
    buffer:setPoint(1, 0.75, -0.75, 0, 1)
    buffer:setPoint(2, -0.75, -0.75, 0, 1)

    buffer:init()

    collectgarbage("collect")
    collectgarbage("collect")
end

