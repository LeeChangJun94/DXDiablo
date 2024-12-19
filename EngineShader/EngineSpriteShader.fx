struct EngineVertex
{
	float4 POSITION : POSITION;
	float4 COLOR : COLOR;
};

// ���ؽ� ���̴��� ������ ���ϰ��� �־�� �մϴ�.
// ��ǲ�����2�� �ѱ� ���� ����������ϴµ�.
// �̶��� ��Ģ�� �ֽ��ϴ�.

struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION;
	float4 COLOR : COLOR;
};

// ���ؽ����̴��� �� �������.
VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
	VertexShaderOutPut OutPut;
	// _Vertex 0.5, 0.5
	OutPut.SVPOSITION = _Vertex.POSITION;
	OutPut.COLOR = _Vertex.COLOR;
	return OutPut;
}

// ���� ���� ��� �Լ�
float crossProduct(float2 p0, float2 p1, float2 p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
    // �ﰢ���� �� ������ ����
    float2 v0 = float2(640.0f, 300.0f); // ù ��° ������
    float2 v1 = float2(570.0f, 420.0f); // �� ��° ������
    float2 v2 = float2(710.0f, 420.0f); // �� ��° ������
    
    float2 v3 = float2(640.0f, 440.0f); // ù ��° ������
    float2 v4 = float2(570.0f, 320.0f); // �� ��° ������
    float2 v5 = float2(710.0f, 320.0f); // �� ��° ������

// �ȼ� ��ġ
    float2 pixelPos = _Vertex.SVPOSITION.xy;

// �ﰢ���� �� ���� ���� ������ ����Ͽ� ����/�ܺ� �Ǵ�
    float cross1 = crossProduct(v0, v1, pixelPos);
    float cross2 = crossProduct(v1, v2, pixelPos);
    float cross3 = crossProduct(v2, v0, pixelPos);

    float cross4 = crossProduct(v3, v4, pixelPos);
    float cross5 = crossProduct(v4, v5, pixelPos);
    float cross6 = crossProduct(v5, v3, pixelPos);
    
// �ﰢ�� ���ο� �ִ��� Ȯ�� (�� ������ ��� ���� ��ȣ���� �ﰢ�� ����)
    if ((cross1 >= 0.0f && cross2 >= 0.0f && cross3 >= 0.0f) ||
    (cross1 <= 0.0f && cross2 <= 0.0f && cross3 <= 0.0f) ||
    (cross4 >= 0.0f && cross5 >= 0.0f && cross6 >= 0.0f) ||
    (cross4 <= 0.0f && cross5 <= 0.0f && cross6 <= 0.0f))
    
    {
        return float4(1.0f - _Vertex.SVPOSITION.x / 1280.0f, 1.0f - _Vertex.SVPOSITION.x / 640.0f, 0.0f, 1.0f); // ������
    }
    else
    {
        return float4(1.0f - _Vertex.SVPOSITION.y / 640.0f, _Vertex.SVPOSITION.y / 640.0f, 0.0f, 1.0f); // �ʷϻ�
    }

}