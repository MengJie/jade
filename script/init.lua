
local source = {
[[
#ifndef GL_ES
    #define highp
    #define mediump
    #define lowp
#endif

uniform     mat4 mvp_matrix;

attribute   vec4 a_position;
attribute   vec4 a_color;

varying mediump vec4 v_color;

void main()
{
    gl_Position = mvp_matrix * a_position;
    v_color     = a_color;
}
]],
[[
#ifndef GL_ES
    #define highp
    #define mediump
    #define lowp
#endif

varying mediump vec4 v_color;

void main()
{
    mediump float lerpValue = gl_FragCoord.y / 500.0;
    gl_FragColor    = mix(v_color,
        vec4(0.0, 0.0, 0.0, 0.2), lerpValue);

    //gl_FragColor = mix(vec4(1.0, 1.0, 1.0, 1.0),
    //    vec4(0.2, 0.2, 0.2, 1.0), lerpValue);
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
    triangles:setPoint(0, 200, 200, 0, 1)
    triangles:setPoint(1, 0, 0, 0, 1)
    triangles:setPoint(2, 0, 200, 0, 1)

    triangles:setColor(0, 1, 0, 0, 1)
    triangles:setColor(1, 0, 1, 0, 1)
    triangles:setColor(2, 0, 0, 1, 1)

    collectgarbage("collect")
    collectgarbage("collect")
end

