﻿#nullable enable

using StateSmith.compiler.Visitors;
using StateSmith.Compiling;
using StateSmith.Input;
using System;
using System.Text;
using System.Linq;
using System.IO;

namespace StateSmith.Runner
{
    public class ExceptionPrinter
    {
        public void DumpExceptionDetails(Exception exception, string filePath)
        {
            StringBuilder sb = new();
            BuildExceptionDetails(sb, exception, additionalDetail: true);
            File.WriteAllText(filePath, sb.ToString());
        }

        public void PrintException(Exception exception)
        {
            StringBuilder sb = new();
            BuildExceptionDetails(sb, exception);
            Console.Error.Write(sb.ToString());
        }

        public void BuildExceptionDetails(StringBuilder sb, Exception exception, bool additionalDetail = false, int depth = 0)
        {
            if (depth > 0)
            {
                sb.AppendLine("==========================");
                sb.AppendLine("Caused by below exception:");
            }

            string? customMessage = TryBuildingCustomExceptionDetails(exception);
            if (customMessage != null)
            {
                sb.AppendLine(customMessage);
            }

            if (additionalDetail || customMessage == null)
            {
                sb.Append($"Exception {exception.GetType().Name} : ");
                sb.AppendLine($"{exception.Message}");
            }

            if (additionalDetail)
            {
                sb.AppendLine($"{exception.StackTrace}");
            }

            if (exception.InnerException != null)
            {
                BuildExceptionDetails(sb, exception.InnerException, additionalDetail, depth + 1);
            }
        }

        public string OutputEdgeDetails(DiagramEdge edge)
        {
            StringBuilder sb = new StringBuilder();
            edge.Describe(sb);
            sb.Append("==========================\n");
            sb.Append("EDGE SOURCE NODE:\n");
            edge.source.Describe(sb);
            sb.Append("\n==========================\n");
            sb.Append("EDGE TARGET NODE:\n");
            edge.target.Describe(sb);

            return sb.ToString();
        }

        public string? TryBuildingCustomExceptionDetails(Exception ex)
        {
            switch (ex)
            {
                case DiagramEdgeParseException parseException:
                    {
                        DiagramEdge edge = parseException.edge;
                        string fromString = VertexPathDescriber.Describe(parseException.sourceVertex);
                        string toString = VertexPathDescriber.Describe(parseException.targetVertex);
                        string reasons = ex.Message.ReplaceLineEndings("\n           ");
                        string message = $@"Failed parsing diagram edge
from: {fromString}
to:   {toString}
Edge label: `{edge.label}`
Reason(s): {reasons}
Edge diagram id: {edge.id}
";
                        return message;
                    }

                case DiagramEdgeException diagramEdgeException:
                    {
                        string message = diagramEdgeException.Message;
                        message += OutputEdgeDetails(diagramEdgeException.edge);
                        return message;
                    }

                case DiagramNodeException diagramNodeException:
                    {
                        string message = diagramNodeException.Message;
                        message += "\n" + DiagramNode.FullyDescribe(diagramNodeException.Node);
                        return message;
                    }

                case VertexValidationException vertexValidationException:
                {
                    string message = nameof(VertexValidationException) + ": " + vertexValidationException.Message;

                    var vertex = vertexValidationException.vertex;
                    string fromString = VertexPathDescriber.Describe(vertex);

message += $@"
    Vertex
    Path: {fromString}
    Diagram Id: {vertex.DiagramId}
    Children count: {vertex.Children.Count()}
    Behaviors count: {vertex.Behaviors.Count()}
    Incoming transitions count: {vertex.IncomingTransitions.Count()}
";
                    return message;
                }


                case BehaviorValidationException behaviorValidationException:
                    {
                        string message = nameof(BehaviorValidationException) + ": " + behaviorValidationException.Message;

                        Behavior behavior = behaviorValidationException.behavior;
                        string fromString = VertexPathDescriber.Describe(behavior.OwningVertex);
                        string toString = VertexPathDescriber.Describe(behavior.TransitionTarget);

                        message += $@"
    Behavior
    Owning vertex: {fromString}
    Target vertex: {toString}
    Order: {behavior.GetOrderString()}
    Triggers: `{string.Join(", ", behavior.triggers)}`
    Guard: `{behavior.guardCode}`
    Action: `{behavior.actionCode}`
    Via Entry: `{behavior.viaEntry}`
    Via Exit : `{behavior.viaExit}`
    Diagram Id: `{behavior.DiagramId}`
";

                        return message;
                    }
            }

            return null;
        }
    }
}
