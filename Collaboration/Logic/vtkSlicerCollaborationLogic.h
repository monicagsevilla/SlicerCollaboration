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

// .NAME vtkSlicerCollaborationLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerCollaborationLogic_h
#define __vtkSlicerCollaborationLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"
#include "vtkXMLDataElement.h"

// MRML includes
#include "vtkMRMLCollaborationNode.h"

// STD includes
#include <cstdlib>

#include "vtkSlicerCollaborationModuleLogicExport.h"


/// \ingroup Slicer_QtModules_ExtensionTemplate
class VTK_SLICER_COLLABORATION_MODULE_LOGIC_EXPORT vtkSlicerCollaborationLogic :
  public vtkSlicerModuleLogic
{
public:

  static vtkSlicerCollaborationLogic *New();
  vtkTypeMacro(vtkSlicerCollaborationLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);
  vtkMRMLCollaborationNode* collaborationNodeSelected;
  void loadAvatars();

  static const char* AVATAR_HEAD_MODEL_NAME;
  static const char* AVATAR_HANDPOINTL_MODEL_NAME;
  static const char* AVATAR_HANDPOINTR_MODEL_NAME;

protected:
  vtkSlicerCollaborationLogic();
  virtual ~vtkSlicerCollaborationLogic();

  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);
  void orderTransforms(vtkXMLDataElement* res);
private:

  vtkSlicerCollaborationLogic(const vtkSlicerCollaborationLogic&); // Not implemented
  void operator=(const vtkSlicerCollaborationLogic&); // Not implemented
};

#endif
