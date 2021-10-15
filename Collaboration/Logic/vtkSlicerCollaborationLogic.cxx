/*==============================================================================

  Copyright (c) EBATINCA, S.L.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Csaba Pinter, EBATINCA, S.L., and
  development was supported by "ICEX Espana Exportacion e Inversiones" under
  the program "Inversiones de Empresas Extranjeras en Actividades de I+D
  (Fondo Tecnologico)- Convocatoria 2021", cofunded by the European Regional
  Development Fund (ERDF).

==============================================================================*/

// Collaboration Logic includes
#include "vtkSlicerCollaborationLogic.h"

// MRML includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>

// STD includes
#include <cassert>

// Collaboration module includes
#include "vtkMRMLCollaborationNode.h"
#include "vtkMRMLCollaborationConnectorNode.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerCollaborationLogic);

//----------------------------------------------------------------------------
vtkSlicerCollaborationLogic::vtkSlicerCollaborationLogic()
{
  vtkSmartPointer<vtkMRMLCollaborationNode> collaborationNode;
}

//----------------------------------------------------------------------------
vtkSlicerCollaborationLogic::~vtkSlicerCollaborationLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerCollaborationLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//---------------------------------------------------------------------------
void vtkSlicerCollaborationLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerCollaborationLogic::RegisterNodes()
{
  //assert(this->GetMRMLScene() != 0);
  vtkMRMLScene* scene = this->GetMRMLScene();
  if (!scene)
  {
    vtkErrorMacro("RegisterNodes: Invalid MRML scene!");
    return;
  }
  if (!scene->IsNodeClassRegistered("vtkMRMLCollaborationNode"))
  {
      scene->RegisterNodeClass(vtkSmartPointer<vtkMRMLCollaborationNode>::New());
  }
  if (!scene->IsNodeClassRegistered("vtkMRMLCollaborationConnectorNode"))
  {
      scene->RegisterNodeClass(vtkSmartPointer<vtkMRMLCollaborationConnectorNode>::New());
  }
}

//---------------------------------------------------------------------------
void vtkSlicerCollaborationLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerCollaborationLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* node)
{
    if (!node || !this->GetMRMLScene())
    {
        vtkErrorMacro("OnMRMLSceneNodeAdded: Invalid MRML scene or input node!");
        return;
    }
    if (node->IsA("vtkMRMLCollaborationNode"))
    {
        // Check if a ConnectorNode for the new CollaborationNode exists
        vtkMRMLCollaborationNode* collaborationNode = vtkMRMLCollaborationNode::SafeDownCast(node);
        char* collabConnectorNodeName = collaborationNode->connectorNodeName;

        if (!collabConnectorNodeName) {
            // Create a ConnectorNode
            vtkMRMLCollaborationConnectorNode* connectorNode =
                vtkMRMLCollaborationConnectorNode::SafeDownCast(this->GetMRMLScene()->CreateNodeByClass("vtkMRMLCollaborationConnectorNode"));
            this->GetMRMLScene()->AddNode(connectorNode);
            // Set the same name as the Collaboration Node + Connector
            char* collaborationNodeName = node->GetName();
            char connectorName[] = "Connector";
            char* connectorNodeName = new char[std::strlen(collaborationNodeName) + std::strlen(connectorName) + 1];
            std::strcpy(connectorNodeName, collaborationNodeName);
            std::strcat(connectorNodeName, connectorName);
            connectorNode->SetName(connectorNodeName);
            collaborationNode->connectorNodeName = connectorNodeName;
            connectorNode->SetType(0);
        }
        this->Modified();
    }
}


//---------------------------------------------------------------------------
void vtkSlicerCollaborationLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* node)
{
  if (!node || !this->GetMRMLScene())
  {
    vtkErrorMacro("OnMRMLSceneNodeRemoved: Invalid MRML scene or input node!");
    return;
  }
  if (node->IsA("vtkMRMLCollaborationNode"))
  {
    vtkMRMLCollaborationNode* collaborationNode = vtkMRMLCollaborationNode::SafeDownCast(node);
    // Get the connector node associated to the collaboration node
    vtkMRMLCollaborationConnectorNode* connectorNode = vtkMRMLCollaborationConnectorNode::SafeDownCast(this->GetMRMLScene()->GetFirstNodeByName(collaborationNode->connectorNodeName));
    this->GetMRMLScene()->RemoveNode(connectorNode);
    this->Modified();
  }
}

