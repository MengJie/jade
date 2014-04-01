
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
        mediump float lerpValue = gl_FragCoord.y / 500.0;
        gl_FragColor = mix(vec4(1.0, 1.0, 1.0, 1.0),
            vec4(0.2, 0.2, 0.2, 1.0), lerpValue);
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

    triangles = Triangles(program)
    triangles:setPoint(0, 0.75, 0.75, 0, 1)
    triangles:setPoint(1, 0.75, -0.75, 0, 1)
    triangles:setPoint(2, -0.75, -0.75, 0, 1)

    collectgarbage("collect")
    collectgarbage("collect")
end

