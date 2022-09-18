using StateSmith.compiler.Visitors;

namespace StateSmith.Compiling
{
    public class EntryPoint : Vertex
    {
        public string label;

        public EntryPoint(string label)
        {
            this.label = label;
        }

        public override void Accept(VertexVisitor visitor)
        {
            visitor.Visit(this);
        }
    }
}
